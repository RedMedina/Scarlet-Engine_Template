#ifndef __TextUI
#define __TextUI

#include <iostream>
#include <map>
#include <string>

#include "Component.h"
#include "CameraMatrix.h"
#include "MainSettings.h"
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <ft2build.h>
#include FT_FREETYPE_H


class TextUI : public Component
{

public:
	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};

	glm::vec3* position;
	glm::vec3* scale;
	glm::vec3* text_color;
	RenderOptions* settings;
	TextUI(const char* fontpath, glm::vec3* pos, glm::vec3* color, std::string Text, glm::vec3* sca);
	void SetMaterial(Material* m);
	void Update() override;
	void Draw() override;

private:
	Material* mat;
	std::map<GLchar, Character> Characters;
	std::vector<glm::vec3> vertices;
	GLuint vertexbuffer;
	GLuint VertexArrayID;
	std::string TextT;
	

	glm::mat4 Canvas_projection;
};


#endif
