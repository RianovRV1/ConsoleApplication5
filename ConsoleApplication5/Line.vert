#version 410


uniform mat4 P;
uniform mat4 MV;
uniform vec3 center;
out vec2 fTexCoord;
out vec4 fragmentColor;
layout(location = 4) in vec4 vPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 3) in vec2 vTexCoord;
void main()
{
	gl_Position = P * (MV * vec4(0,0,0,1) + vec4(vPosition.x, vPosition.y, 0.0 ,0.0));
	fTexCoord = vTexCoord;
	fragmentColor = vertexColor;
}