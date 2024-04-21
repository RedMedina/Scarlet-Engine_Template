#ifndef __Debug
#define __Debug

static class Debug
{
private:
	static bool Debug_Mode;

public:
	static bool GetDebugMode();
	static void SetDebugMode(bool debug);
};

#endif