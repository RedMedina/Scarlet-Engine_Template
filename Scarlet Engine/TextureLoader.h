#ifndef __TextureLoader
#define __TextureLoader

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class TextureLoader
{
public:
	GLuint LoadTexture2D(const char* ruta_textura)
	{
		GLuint id_textura;
		glGenTextures(1, &id_textura);

		int ancho, alto, numero_canales;
		unsigned char* datos_textura = stbi_load(ruta_textura, &ancho, &alto, &numero_canales, 0);
		if (datos_textura)
		{
			GLenum formato_datos_textura;
			if (numero_canales == 1)
				formato_datos_textura = GL_RED;
			else if (numero_canales == 3)
				formato_datos_textura = GL_RGB;
			else if (numero_canales == 4)
				formato_datos_textura = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, id_textura);
			glTexImage2D(GL_TEXTURE_2D, 0, formato_datos_textura, ancho, alto, 0, formato_datos_textura, GL_UNSIGNED_BYTE, datos_textura);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(datos_textura);
		}
		else
		{
			std::cout << "Error al cargar la textura en la ruta: " << ruta_textura << std::endl;
			stbi_image_free(datos_textura);
		}

		return id_textura;
	}

	GLuint FrameBuffer()
	{
		GLuint framebuffer;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		return framebuffer;
	}

	GLuint FrameDepthBuffer()
	{
		GLuint framebuffer;
		glGenFramebuffers(1, &framebuffer);

		return framebuffer;
	}

	GLuint DepthMap(int w_texture, int h_texture, GLuint depthMapFBO)
	{
		GLuint depthMap;
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w_texture, h_texture, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		Unbind_FrameBuffer();

		return depthMap;
	}

	GLuint RenderDepthTexture(int w_texture, int h_texture)
	{
		GLuint renderTexture;
		glGenTextures(1, &renderTexture);
		glBindTexture(GL_TEXTURE_2D, renderTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w_texture, h_texture, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, renderTexture, 0);

		return renderTexture;
	}

	void Bind_FrameBuffer(GLuint framebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		//glBindTexture(GL_TEXTURE_2D, renderTexture);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Bind_DepthFrameBuffer(GLuint framebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Unbind_FrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint RenderBuffer(int w_texture, int h_texture)
	{
		GLuint renderbuffer;
		glGenRenderbuffers(1, &renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w_texture, h_texture);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
		
		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		Unbind_FrameBuffer();

		return renderbuffer;
	}

	GLuint RenderTexture(int w_texture, int h_texture, int channel)
	{
		GLuint renderTexture;
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + channel);
		glGenTextures(1, &renderTexture);
		glBindTexture(GL_TEXTURE_2D, renderTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w_texture, h_texture, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + channel, GL_TEXTURE_2D, renderTexture, 0);

		return renderTexture;
	}

};

#endif