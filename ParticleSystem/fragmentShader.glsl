#version 330 core

out vec4 color;

in float Type;

void main()
{
	
	const vec4 color1=vec4(0.6,0.0,0.0,1.0);
	const vec4 color2=vec4(0.9,0.7,1.0,0.0);
	vec2 temp=gl_PointCoord - vec2(0.5);
	float f=dot(temp,temp);
	if (f>0.25)
		discard;

	color=mix(color1,color2,smoothstep(0.1,0.25,f));
	
	if(abs(Type-2.0)<0.0001 || abs(Type-1.0)<0.0001)
		color=vec4(1,0,0,1);
	else
		color=vec4(0,1,0,1);

}