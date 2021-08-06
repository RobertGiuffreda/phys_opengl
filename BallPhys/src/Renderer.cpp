#include <iostream>
#include "Renderer.h"

void GLClearError()
{
    // while glGetError != GL_NO_ERROR
    while (!glGetError());
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error]: (" << error << ")" << function <<
            " " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetClearColor(float f0, float f1, float f2, float f3) const
{
    glClearColor(f0, f1, f2, f3);
}

void Renderer::EnableDepthTest() const
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();

    // Below line of code is unnecessary as array buffer was bound to vao before <- Maybe test this
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawWireframe(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();

    // Below line of code is unnecessary as array buffer was bound to vao before <- Maybe test this
    ib.Bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/* Draw function used for vertex arrays without an index buffer */
void Renderer::Draw(const VertexArray& va, const Shader& shader, const unsigned int count) const
{
    shader.Bind();
    va.Bind();
    // Unbind any bound index buffer array
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, count);
}