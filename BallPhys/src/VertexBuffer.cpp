#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer() : id(0) {
    glGenBuffers(1, &id);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

/* 
Function to create buffer and fill buffer if the
data was not provided in the call to the constructor
*/
void VertexBuffer::FillBuffer(const void* data, unsigned int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

