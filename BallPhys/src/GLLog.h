#pragma once

// Compiler instrinsic function to call. DIfferent for each compiler
#define ASSERT(x) if (!(x)) __debugbreak();

// GlCall(function to check)
#define GLCall(x) GlClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
