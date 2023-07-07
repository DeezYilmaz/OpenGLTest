#version 330 core 


in vec3 color;
uniform vec2 MousePos;
out vec4 FragColor; 


void main()
{ 
	FragColor = vec4(color.x,color.y,color.z, 1.0f); 
}