
#version 410
in vec3 fragmentColor;
out vec4 color;

void main()
{
	
	//color = vec4(1);
	color = vec4(fragmentColor, 1);
}
