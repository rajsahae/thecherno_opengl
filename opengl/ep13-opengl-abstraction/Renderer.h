#pragma once

#include <GL/glew.h>
#include <assert.h>

#define ASSERT(x) if (!(x)) assert(false)

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())

void GLClearError();
bool GLCheckError();
