#version 410
in vec4 fragmentColor;
in vec2 fTexCoord;
out vec4 color;
uniform sampler2D tex;

void main()
{
	//color = vec4(0.2,0.2,0.2,0);
	
	color = vec4(fragmentColor);
	color += texture(tex, fTexCoord)*vec4(1,1,1,0.2);
	
}
