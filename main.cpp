//
//  main.cpp
//  Bilgisayar Proje II - Real-Time Computer Graphics
//  Project #III - Fresnel Effect
//
//  Merter TURAN - turanmerter@gmail.com
//  040080204
//
#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include "Scene.h"
#include "NormalShaderNode.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define WINDOW_TITLE_PREFIX "Proje 3"

void IdleFunction(void);
void ResizeFunction(int Width, int Height);
void setupScene();

int CurrentWidth = 800,
CurrentHeight = 600;

SceneNode* bunny;
Camera *camera;
Scene* scene;

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    scene->draw();
    
    glutSwapBuffers();
}

void SpecialKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT:
			bunny->r0 -= 0.1;
			printf("Reflectance is decreased.\n");
			break;
		case GLUT_KEY_RIGHT:
			bunny->r0 += 0.1;
			printf("Reflectance is increased.\n");
			break;
		case GLUT_KEY_UP:
			bunny->r1 += 0.1;
			printf("Power is increased.\n");
			break;
		case GLUT_KEY_DOWN:
			bunny->r1 -= 0.1;
			printf("Power is decreased.\n");
			break;
	}
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

static void timerCallback (int value)
{
    if (0 != value) {
		char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));
        
		sprintf(
                TempString,
                "%s @ %d x %d",
                WINDOW_TITLE_PREFIX,
                CurrentWidth,
                CurrentHeight
                );
        
		glutSetWindowTitle(TempString);
		free(TempString);
	}
	glutTimerFunc(250, timerCallback, 1);
}

void IdleFunction(void)
{
	glutPostRedisplay();
}

void setupScene(){
    scene = new Scene();
    bunny = new NormalShaderNode("bunny.obj");
    
    scene->addNode(bunny);
    camera = new Camera();
    camera->translate(0.f, 0.f, 0.5);
    scene->setCamera(camera);
}

int main (int argc, char ** argv)
{
    
    GLenum type;
    
	glutInit(&argc, argv);
	
	glutInitWindowSize(CurrentWidth,CurrentHeight);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("");
    glewInit();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    // Z-Buffer i aciyoruz
    glEnable(GL_DEPTH_TEST);
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
    
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("GLSL Version: %s\n",glslVersion);
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    
    printf("GL Version: %s\n",glVersion);
       
    setupScene();
    
    timerCallback(0);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(Draw);
	glutSpecialFunc(SpecialKey);
    glutIdleFunc(IdleFunction);

	printf("\nBilgisayar Proje II - Real-Time Computer Graphics\n");
	printf("Project #III - Fresnel Effect\n\n");
	printf("Commands:\n");
	printf("---------\n");
	printf("	UP:    Increase power.\n");
	printf("	DOWN:  Decrease power\n");
	printf("	RIGHT: Increase reflectance\n");
	printf("	LEFT:  Decrease reflectance\n\n");

    glutMainLoop();
    
    return 0;
}


