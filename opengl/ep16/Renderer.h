#pragma once

#include <GL/glew.h>
#include <assert.h>
#include <stdint.h>

#define ASSERT(x) if (!(x)) assert(false)

#ifdef DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())
#else
#define GLCall(x) x
#endif

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

void GLClearError();
bool GLCheckError();
