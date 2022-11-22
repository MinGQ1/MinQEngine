#pragma once
#include<string>

class Layer
{
public:
	virtual void Update();
	virtual std::string GetName();
};