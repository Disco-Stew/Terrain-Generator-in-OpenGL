#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D textureToApply;

void main()
{    
	//vec2 fail = vec2(1.0,1.0);
	//vec4 brightLight = vec4(1.0,1.0,1.0,1.0);
	//color = brightLight * texture(textureToApply, TexCoords);
	color = texture(textureToApply, TexCoords);
}