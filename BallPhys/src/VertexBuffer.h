#pragma once
#include <vector>
#include <glad/glad.h>

class VertexBuffer
{
private:
	unsigned int id;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void FillBuffer(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;
};