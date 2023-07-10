#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;


uniform mat4 transform;
out vec2 TexCoord;
out vec3 color;

void main()
{	
	gl_Position = transform*vec4(aPos,1.0f);
	color=vec3(0.f,0.f,0.f);	
    TexCoord = aTexture;
}