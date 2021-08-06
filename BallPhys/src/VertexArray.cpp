#include "VertexArray.h"

VertexArray::VertexArray() : stride(0)
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);
}

template <typename T>
void VertexArray::AddVertexBufferElement(unsigned int count)
{
	static_assert(false);
}

template<>
void VertexArray::AddVertexBufferElement<float>(unsigned int count)
{
	elements.push_back({ GL_FLOAT, count, GL_FALSE, sizeof(GLfloat) });
	stride += count * sizeof(GLfloat);
}

template<>
void VertexArray::AddVertexBufferElement<unsigned int>(unsigned int count)
{
	elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, sizeof(GLuint) });
	stride += count * sizeof(GLuint);
}

template<>
void VertexArray::AddVertexBufferElement<unsigned char>(unsigned int count)
{
	elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE, sizeof(GLbyte) });
	stride += count * sizeof(GLbyte);
}

void VertexArray::AddBuffer(const VertexBuffer& vb)
{
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		VertexBufferElement element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, stride, (void *)offset);
		offset += element.count * element.sizeof_type;
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}