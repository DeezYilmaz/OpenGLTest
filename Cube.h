#pragma once

#include "VertexBuffer.h"
#include "Drawable.h"
#include <memory>

#include <vector>
class Cube:public Drawable {
public:

	std::vector<std::shared_ptr<Bindable>> bindableList;
	Cube();
	void draw() override;
};