#include "Material.h"

Material::Material(const char* vertexshader, const char* fragmentshader)
{
	shader = new Shader;
	ShaderProgram = shader->LoadShaders(vertexshader, fragmentshader);
	Material_Settings = new Options;
	textureloader = new TextureLoader;
}

void Material::Set_Config(RenderOptions* options)
{
	options->Transparency(Material_Settings->Transparent);
	options->ZBuffer(Material_Settings->Z_On);
	if(Material_Settings->Z_Equal)
	{
		options->SetDepth(GL_LEQUAL);
	}
	if(Material_Settings->Cull_Front)
	{
		options->Face_Mode(GL_FRONT);
	}
	else if(Material_Settings->Cull_Equal)
	{
		options->Face_Mode(GL_FRONT_AND_BACK);
	}
}

void Material::End_Config(RenderOptions* options)
{
	options->Transparency(false);
	options->ZBuffer(true);
	options->SetDepth(GL_LESS);
	options->Face_Mode(GL_BACK);
}

void Material::BindTextures()
{
	for (int i = 0; i < Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, Textures[i].IdTexture);
		SetInteger(Textures[i].Name, i);
		//std::cout << "SHADOW MAP ID TEXTURE " << Textures[i].IdTexture << endl;
	}
}

void Material::BindRenderTextures()
{
	for (int i = 0; i < Framebuffers.size(); i++)
	{
		textureloader->Bind_FrameBuffer(Framebuffers[i]);
		//textureloader->Bind_FrameBuffer(2, 2);
		//std::cout << "POST PROCESS ID TEXTURE " << Textures[i].IdTexture << endl;
	}
}

void Material::UnBindRenderTextures()
{
	textureloader->Unbind_FrameBuffer();
}

void Material::SetTexture2D(const char* Name, const char* texturepath)
{
	Texture tex;
	tex.IdTexture = textureloader->LoadTexture2D(texturepath);
	tex.Name = Name;
	Textures.push_back(tex);
}

void Material::SetRenderTexture(const char* Name, int w_screen, int h_screen)
{
	GLuint fbo = textureloader->FrameBuffer();
	Framebuffers.push_back(fbo);

	std::cout << "POST ID TEXTURE " << fbo << endl;
	
	Texture tex;
	tex.IdTexture = textureloader->RenderTexture(w_screen, h_screen, 0);
	std::cout << "POST PROCESS FBO " << fbo << endl;
	tex.Name = Name;
	Textures.push_back(tex);

	//GLuint rbo = textureloader->RenderBuffer(w_screen, h_screen);
	//Renderbuffers.push_back(rbo);
}

void Material::SetValue(const char* Name, int value)
{
	SetInteger(Name, value);
}

void Material::SetValue(const char* Name, float value)
{
	SetFloat(Name, value);
}

void Material::SetValue(const char* Name, glm::vec2 value)
{
	SetVec2(Name, value);
}

void Material::SetValue(const char* Name, glm::vec3 value)
{
	SetVec3(Name, value);
}

void Material::SetValue(const char* Name, glm::vec4 value)
{
	SetVec4(Name, value);
}

void Material::SetValue(const char* Name, glm::mat3 value)
{
	SetMat3(Name, value);
}

void Material::SetValue(const char* Name, glm::mat4 value)
{
	SetMat4(Name, value);
}

void Material::Update()
{
	//aaa---
}

void Material::Draw()
{
	glUseProgram(ShaderProgram);
	BindTextures();
}

//void Draw() override;

void Material::SetInteger(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(ShaderProgram, name), value);
	
}

void Material::SetFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(ShaderProgram, name), value);
}

void Material::SetVec2(const char* name, glm::vec2 value)
{
	glUniform2f(glGetUniformLocation(ShaderProgram, name), value.x, value.y);
}

void Material::SetVec3(const char* name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(ShaderProgram, name), value.x, value.y, value.z);
}

void Material::SetVec4(const char* name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(ShaderProgram, name), value.r, value.g, value.b, value.a);
}

void Material::SetMat3(const char* name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(ShaderProgram, name), 1, GL_FALSE, &value[0][0]);
}

void Material::SetMat4(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name), 1, GL_FALSE, &value[0][0]);
}

Material::~Material()
{
	delete shader;
	delete Material_Settings;
}