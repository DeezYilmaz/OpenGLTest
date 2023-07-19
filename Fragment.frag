#version 330 core 


in vec3 color;
in vec2 TexCoord;

uniform vec2 MousePos;
uniform sampler2D ourTexture;

out vec4 FragColor; 


void main()
{ 
	
	FragColor = vec4(1f,1f,1f,1f);
}