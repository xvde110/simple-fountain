#version 330 core
layout (location = 0) in vec3 position;


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;



void main()
{
	vec4 pos=projectionMatrix * (viewMatrix * vec4(position,1.0));
	//vec4 pos=vec4(position,1.0);
	gl_PointSize=(1.0-pos.z/pos.w)*8;
	gl_Position=pos;

}