#include "Texture.h"

#include <iostream>

#include "../stb_image/stb_image.h"

int Texture::textureCount = 0;

Texture::Texture(const char* filename)
{
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + textureCount);
	textureNumber = textureCount;
	textureCount++;

	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data)
	{
		GLint format;
		if (nrChannels == 4)
		{
			format = GL_RGBA;
		}
		else if (nrChannels == 3)
		{
			format = GL_RGB;
		}
		else if (nrChannels == 2)
		{
			format = GL_RG;
		}
		else
		{
			format = GL_RED;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + textureNumber);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
