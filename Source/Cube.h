#pragma once

#include "VertexBuffer.h"
#include "Drawable.h"
#include <memory>
#include <glm/fwd.hpp>

#include <vector>
class Cube:public Drawable {
public:
	std::shared_ptr<glm::mat4> modelMatrix;
	int modelUniformLocation;
	std::vector<std::shared_ptr<Bindable>> bindableList;
	Cube();
	void draw() override;
	void moveObject(glm::vec3 *translationVector);
	void setUniforms(int modelUniform);
};