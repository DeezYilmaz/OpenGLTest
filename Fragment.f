#version 330 core 


in vec3 color;
uniform vec2 MousePos;
out vec4 FragColor; 


void main()
{ 
	FragColor = vec4(color.x,MousePos.x,MousePos.y, 1.0f); 
}