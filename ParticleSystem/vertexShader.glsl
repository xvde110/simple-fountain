#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in float type;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out float Type;

void main()
{
	vec4 pos=projectionMatrix * (viewMatrix * vec4(position,1.0));
	//vec4 pos=vec4(position,1.0);
	gl_PointSize=(1.0-pos.z/pos.w)*8;
	gl_Position=pos;
	Type=type;
}