#pragma once

#include "VertexBuffer.h"
#include "Drawable.h"
#include <memory>
#include <glm/fwd.hpp>

#include <vector>
class Cube:public Drawable {
public:
	std::shared_ptr<glm::mat4> modelMatrix;
	std::vector<std::shared_ptr<Bindable>> bindableList;
	Cube();
	void draw() override;
	void moveObject(glm::vec3 *translationVector);
};