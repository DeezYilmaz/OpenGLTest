#pragma once
#include "Bindable.h"
class Drawable {
public:
	virtual ~Drawable() = default;
	virtual void draw() = 0;
};