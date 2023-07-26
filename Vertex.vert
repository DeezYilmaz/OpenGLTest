#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;


uniform mat4 model;
uniform mat4 projectAndCamera;

out vec2 TexCoord;
out vec3 color;

void main()
{	
	gl_Position =projectAndCamera*model*vec4(aPos,1.0f);
	color=vec3(1.f,0.f,0.f);	
    TexCoord = aTexture;
}