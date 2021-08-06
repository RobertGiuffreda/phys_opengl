#pragma once
#include <vector>
#include <glad/glad.h>
#include "VertexBuffer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	unsigned int sizeof_type;
};

class VertexArray
{
private:
	unsigned int id;							// VertexArray ID from opengl
	std::vector<VertexBufferElement> elements;	// Array of data about each element
	unsigned int stride;						// Size of each vertex

public:
	VertexArray();
	~VertexArray();

	template<typename T>
	void AddVertexBufferElement(unsigned int count);

	void AddBuffer(const VertexBuffer& vb);

	void Bind() const;
	void Unbind() const;
};