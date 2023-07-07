#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat3 rotationMatrix;

out vec3 color;

void main()
{
	vec3 finalPos= aPos*rotationMatrix;
	gl_Position = vec4(finalPos.x, finalPos.y, finalPos.z, 1.0);
	color=aColor;		
}