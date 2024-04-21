#include "Shader.h"

Shader::Shader() {}

GLuint Shader::LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	//Crea los shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Lee el vertex shader
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("No se puede abrir el vertex shader %s. Revisa si es el directorio correcto. \n", vertex_file_path);
		getchar();
		return 0;
	}

	//Lee el fragment/pixel shader
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("No se puede abrir el fragment/pixel shader %s. Revisa si es el directorio correcto. \n", fragment_file_path);
		getchar();
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// compila el vertex shader
	printf("Compilando shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Revisa el vertex shader si hay un error
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}


	// compila el fragment/pixel shader
	printf("Compilando shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Revisa el fragment/pixel shader si hay un error
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Linkea el shader
	printf("Linking shader\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Revisa si el shader no tiene errores
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	//Genera los detectores de uniforms
	parseShader(vertex_file_path, fragment_file_path);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void Shader::parseShader(const std::string& filePath_vertex, const std::string& filePath_fragment) {

	//Revisión del vertex shader
	std::ifstream fileStream(filePath_vertex);
	std::string line;

	while (std::getline(fileStream, line)) {
		size_t namePos = line.find("@uniform_name");
		size_t typePos = line.find("@uniform_type");

		if (namePos != std::string::npos) {
			// Extracción del nombre de la variable uniforme
			size_t pos = namePos + 13; // Longitud de "@uniform_name "
			std::string uniformName = line.substr(pos);
			uniforms_vertex.push_back({ uniformName });
		}
		else if (typePos != std::string::npos) {
			// Extracción del tipo de la variable uniforme
			size_t pos = typePos + 13; // Longitud de "@uniform_type "
			std::string uniformType = line.substr(pos);
			uniforms_vertex.back().type = uniformType;
		}
	}

	//Revisión del fragment/pixel shader
	std::ifstream fileStream2(filePath_fragment);
	std::string line2;

	while (std::getline(fileStream2, line2)) {
		size_t namePos = line2.find("@uniform_name");
		size_t typePos = line2.find("@uniform_type");

		if (namePos != std::string::npos) {
			// Extracción del nombre de la variable uniforme
			size_t pos = namePos + 13; // Longitud de "@uniform_name "
			std::string uniformName = line2.substr(pos);
			uniforms_fragment.push_back({ uniformName });
		}
		else if (typePos != std::string::npos) {
			// Extracción del tipo de la variable uniforme
			size_t pos = typePos + 13; // Longitud de "@uniform_type "
			std::string uniformType = line2.substr(pos);
			uniforms_fragment.back().type = uniformType;
		}
	}
}