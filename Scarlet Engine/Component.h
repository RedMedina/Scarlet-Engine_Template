#ifndef __Component
#define __Component

#include <vector>

class Component
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif