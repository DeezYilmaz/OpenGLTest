#pragma once

#include "Bindable.h"
#include <vector>

class VertexBuffer:public Bindable {
public:
	unsigned int VBO, VAO;
	VertexBuffer(const float *vertices, int buffersize, std::vector<int> attributeList);
	~VertexBuffer() override;
	void bind() override;
	void assignVertexAttributes(std::vector<int> attributeList);
};