#pragma once

#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* filename);
	~Texture();

	void Bind() const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline int GetTextureNumber() const { return textureNumber; }

private:
	static int textureCount;
	int textureNumber;
	unsigned int id;
	int width, height, nrChannels;
};

