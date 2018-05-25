// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

void ClearAll()
{
    GLCall( glUseProgram(0) );
    GLCall( glBindBuffer(GL_ARRAY_BUFFER, 0) );
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
    GLCall( glBindVertexArray(0) );
}

int main( void )
{
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;

    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    {
        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        IndexBuffer ib(indices, 6);

        VertexBufferLayout layout;
        layout.AddFloat(2);

        va.AddBuffer(vb, layout);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        float red = 0.0f;
        float step = 0.05f;

        ClearAll();

        do {
            // Clear the screen
            GLCall( glClear( GL_COLOR_BUFFER_BIT );

            // set shader and set uniform color
            shader.Bind();
            shader.SetUniform4f("u_Color", red, 0.3, 0.8, 1.0);

            // Bind index buffer
            va.Bind();
            ib.Bind();

            // Draw
            GLCall( glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)) );

            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();

            // increment red
            if (red < 0.0f || red > 1.0f)
                step *= -1.0;
            red += step;

        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0 );
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

