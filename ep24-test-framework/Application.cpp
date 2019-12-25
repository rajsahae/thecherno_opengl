// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTriangle.h"
#include "tests/TestUniform.h"
#include "tests/TestMultipleObjects.h"

#include "Debug.h"

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

    std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
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

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    int currentSelection = -1;
    int radioSelection = 0;
    test::Test *test;

    do {
        ImGui_ImplGlfwGL3_NewFrame();
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::RadioButton("ClearColor",      &radioSelection, 0); ImGui::SameLine();
            ImGui::RadioButton("Triangle",        &radioSelection, 1); ImGui::SameLine();
            ImGui::RadioButton("Uniform",         &radioSelection, 2); ImGui::SameLine();
            ImGui::RadioButton("MultipleObjects", &radioSelection, 3);
        }

        if (currentSelection != radioSelection)
        {
            switch(radioSelection)
            {
                case 0 : delete test;
                         test = new test::TestClearColor();
                         break;
                case 1 : delete test;
                         test = new test::TestTriangle();
                         break;
                case 2 : delete test;
                         test = new test::TestUniform();
                         break;
                case 3 : delete test;
                         test = new test::TestMultipleObjects();
                         break;
            }
            currentSelection = radioSelection;
        }

        test->OnUpdate(0.0f);
        test->OnRender();
        test->OnImGuiRender();

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );

    // Close OpenGL window and terminate GLFW
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

