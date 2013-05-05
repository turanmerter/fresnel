#version 120

// sabit degiskenler
uniform mat4 MVP;

// diziden alinacak degiskenler
attribute vec4 Position;
attribute vec3 Normal;

uniform float Reflectance;
uniform float Power;

// fragment shader'a aktarilacak veriler
varying vec3 normal;
varying float r0;
varying float r1;

// vertex shader main metodu
void main()
{	
    // gl_Position ekranda noktanin nerede olacagini belirtir.
    gl_Position = MVP * Position;
    normal = mat3(MVP)*Normal;
	r0 = Reflectance;
	r1 = Power;
}