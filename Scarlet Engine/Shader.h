#ifndef __Shader
#define __Shader

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
#include <stdlib.h>
#include <string.h>
#include <glew.h>

class Shader
{
private:
	struct UniformInfo {
		std::string name;
		std::string type;
		// Otros detalles sobre la variable uniforme si es necesario
	};
	void parseShader(const std::string& filePath_vertex, const std::string& filePath_fragment);
public:
	Shader();
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	std::vector<UniformInfo> uniforms_vertex;
	std::vector<UniformInfo> uniforms_fragment;
};

#endif