#version 410


uniform mat4 P;
uniform mat4 MV;
out vec2 fTexCoord;
out vec3 fragmentColor;
layout(location = 0) in vec4 vPosition;

layout(location = 2) in vec2 vTexCoord;
void main()
{
    
	gl_Position = P * MV * vPosition;
	fTexCoord = vTexCoord;
	
}      