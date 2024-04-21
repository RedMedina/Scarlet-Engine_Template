#include "Debug.h"

bool Debug::Debug_Mode = false;

bool Debug::GetDebugMode()
{
	return Debug_Mode;
}

void Debug::SetDebugMode(bool debug)
{
	Debug_Mode = debug;
}