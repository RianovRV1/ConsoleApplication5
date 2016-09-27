
#version 410

in vec2 fTexCoord;
out vec4 color;
uniform sampler2D tex;
void main()
{
	//color = vec4(1,0,0,1);
	color += texture(tex, fTexCoord);
	//color = vec4(1,1,1,1);
	//color = vec4(1,0,0,1);
	//color = vec4(fragmentColor, 1);
}
