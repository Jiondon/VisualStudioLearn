#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 TexCoord;

void main()
{
	FragColor = vec4(TexCoord,1.0);
}