#ifndef __Material
#define __Material

#include "Component.h"
#include "Shader.h"
#include "TextureLoader.h"
#include "RenderOptions.h"
#include <glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class Material : public Component
{
public:
	struct Options {
		bool Opaque = true;
		bool Transparent = false;
		bool Cull_back = true;
		bool Cull_Front = false;
		bool Cull_Equal = false;
		bool Z_Equal = false;
		bool Z_On = true;
	};

	struct Texture
	{
		GLuint IdTexture;
		const char* Name;
	};

	Options* Material_Settings;
	std::vector<Texture> Textures;

	Material(const char* vertexshader, const char* fragmentshader);
	void Update() override;
	void Draw() override;
	void Set_Config(RenderOptions* options);
	void End_Config(RenderOptions* options);
	void BindTextures();
	void BindRenderTextures();
	void UnBindRenderTextures();
	void SetInteger(const char* name, int value);
	void SetFloat(const char* name, float value);
	void SetVec2(const char* name, glm::vec2 value);
	void SetVec3(const char* name, glm::vec3 value);
	void SetVec4(const char* name, glm::vec4 value);
	void SetMat3(const char* name, glm::mat3 value);
	void SetMat4(const char* name, glm::mat4 value);
	void SetValue(const char* Name, int value);
	void SetTexture2D(const char* Name, const char* texturepath);
	void SetRenderTexture(const char* Name, int w_screen, int h_screen);
	void SetValue(const char* Name, float value);
	void SetValue(const char* Name, glm::vec2 value);
	void SetValue(const char* Name, glm::vec3 value);
	void SetValue(const char* Name, glm::vec4 value);
	void SetValue(const char* Name, glm::mat3 value);
	void SetValue(const char* Name, glm::mat4 value);
	~Material();

private:
	Shader* shader;
	TextureLoader* textureloader;
	GLuint ShaderProgram;
	std::vector<GLuint> Framebuffers;
	std::vector<GLuint> Renderbuffers;
};

#endif