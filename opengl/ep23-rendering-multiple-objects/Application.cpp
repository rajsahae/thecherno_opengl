// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

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
    GLFWwindow* window = glfwCreateWindow( 960, 540, "Tutorial 02 - Red triangle", NULL, NULL);
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

int main( void )
{
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;

    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f, // 0
        200.0f, 100.0f, 1.0f, 0.0f, // 1
        200.0f, 200.0f, 1.0f, 1.0f, // 2
        100.0f, 200.0f, 0.0f, 1.0f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    {
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        IndexBuffer ib(indices, 6);

        // projection matrix
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

        // view matrix
        glm::mat4 ident = glm::mat4(1.0f);
        glm::vec3 trvec = glm::vec3(-100, 0, 0);
        glm::mat4 view = glm::translate(ident, trvec);

        VertexBufferLayout layout;
        layout.AddFloat(2);
        layout.AddFloat(2);

        va.AddBuffer(vb, layout);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/phone.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        float red = 0.0f;
        float step = 0.05f;

        Renderer renderer;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        glm::vec3 translation(200, 200, 0);

        do {
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();

            // model matrix
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;

            shader.Bind();
            shader.SetUniform4f("u_Color", red, 0.3, 0.8, 1.0);
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);

            {
                ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

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
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

