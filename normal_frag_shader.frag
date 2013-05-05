#version 120

// vertex shaderindan gelen veriler
varying vec3 normal;
varying float r0;
varying float r1;

// fragment shader main metodu
void main(void)
{
    // gl_FragColor ekrana basilacak rengi secer

	//float r0 = 0.5; //reflectance 0 - 1
	//float r1 = 3.0; //power 0 - 20

	float cosin = dot(normalize(normal), vec3(0.0, 0.0, -1.0));
	float fresnel = (r0 + ((1-r0) * pow((1+cosin), r1)))/2.5;


	gl_FragColor = vec4(mix(1.0,0.0,fresnel),mix(0.0,0.0,fresnel),mix(0.0,1.0,fresnel),1.0);
	//gl_FragColor = vec4(mix(1.0,0.0,cosin),mix(0.0,0.0,cosin),mix(0.0,1.0,cosin),1.0);
    //gl_FragColor = vec4(normalize(normal),1.0);
}
