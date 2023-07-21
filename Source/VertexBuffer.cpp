#include "VertexBuffer.h"
#include <iostream>
#include "glad/glad.h"
#include "glfw3.h"

VertexBuffer::VertexBuffer(const float *vertices,int buffersize, std::vector<int> attributeList)
{

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, buffersize, vertices, GL_STATIC_DRAW);

	assignVertexAttributes(attributeList);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&VAO);
}

void VertexBuffer::bind()
{
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

}

void VertexBuffer::assignVertexAttributes(std::vector<int> attributeList ) {
	int sum = 0;

	for (size_t i = 0; i < attributeList.size(); i++)
	{
		sum += attributeList[i];
	}
	int currentSum = 0;
	for (size_t i = 0; i < attributeList.size(); i++)
	{
		glVertexAttribPointer(i, attributeList[i], GL_FLOAT, GL_FALSE, sum * sizeof(float), (void*)(currentSum*sizeof(float)));
		currentSum += attributeList[i];
		glEnableVertexAttribArray(i);
	}

}
