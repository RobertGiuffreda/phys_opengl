#pragma once

#include <glad/glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
    void Clear() const;
    void SetClearColor(float f0, float f1, float f2, float f3) const;
    void EnableDepthTest() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawWireframe(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const VertexArray& va, const Shader& shader, const unsigned int count) const;
};