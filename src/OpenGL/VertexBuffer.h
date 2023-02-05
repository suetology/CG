#pragma once

#include "GL/glew.h"

enum class Type
{
	MESH,
	LINES
};

class VertexBuffer
{
public:
	VertexBuffer(Type type, const void* vertices, GLsizeiptr size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int id;
};

