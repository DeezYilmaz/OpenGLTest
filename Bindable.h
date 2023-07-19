#pragma once


class Bindable 
{
public:
	virtual ~Bindable() = default;
	virtual void bind() = 0;
};