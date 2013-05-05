//
//  NormalShaderNode.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/1/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef NormalShaderNode_h
#define NormalShaderNode_h
#include <windows.h>
#include "Camera.h"
#include "ShadedGeometry.h"

class NormalShaderNode: public ShadedGeometry{
public:
    NormalShaderNode(char *filename):
    ShadedGeometry(filename,
                   "normal_vert_shader.vert",
                   "normal_frag_shader.frag")
    {
        generateBuffers();
		r0 = 0.5;
		r1 = 3.0;
    }
    ~NormalShaderNode(){
        
    }
    void draw(SceneNode *camera){

        glUseProgram(programId);
        
        glm::mat4 MVPmatrix = ((Camera*)camera)->projectionMatrix * camera->getInverseModelMatrix() * getModelMatrix();
        
        glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVPmatrix[0][0]);
        glUniform1f(reflectance, r0 );
		glUniform1f(power, r1 );
        
        // vertex bufferi bagla
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // normal buffer i bagla
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // indiceleri bagla
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);
        
        // Attributelari enable et
        glEnableVertexAttribArray(AttributePosition);
        glEnableVertexAttribArray(AttributeNormal);
        
        // ciz
        glDrawElements(GL_TRIANGLES, int(faceArray.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
        
        
        // baglantilari kopar
        glDisableVertexAttribArray(AttributeNormal);
        glDisableVertexAttribArray(AttributePosition);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        
        glUseProgram(0);
    }

	void setPower(GLfloat power) {

	}
private:
    GLuint UniformMVP;
    GLuint AttributePosition,AttributeNormal;
    GLuint reflectance;
	GLuint power;
    
    void generateBuffers(){
        
        UniformMVP = glGetUniformLocation(programId, "MVP");
        printf("UniformMVP: %d\n",UniformMVP);
        
        AttributePosition = glGetAttribLocation(programId, "Position");
        printf("Position Attribute: %d\n", AttributePosition);
        
        AttributeNormal = glGetAttribLocation(programId, "Normal");
        printf("Normal Attribute: %d\n", AttributeNormal);
        
		reflectance = glGetUniformLocation(programId, "Reflectance");
        printf("Reflectance: %d\n",reflectance);

		power = glGetUniformLocation(programId, "Power");
        printf("Power: %d\n",power);
    }
};

#endif
