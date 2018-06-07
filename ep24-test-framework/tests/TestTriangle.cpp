#include "tests/TestTriangle.h"

#include "Debug.h"
#include "imgui.h"

namespace test
{
    TestTriangle::TestTriangle() :
        m_ClearColor { 0.8f, 0.3f, 0.2f, 1.0f },
        m_Positions {
            -0.5f, -0.5f, // 0
             0.5f, -0.5f, // 1
             0.5f,  0.5f, // 2
        },
        m_va(),
        m_vb(m_Positions, 3 * 2 * sizeof(float)),
        m_layout(),
        m_shader("res/shaders/Simple.shader")
    {
        m_layout.AddFloat(2);
        m_va.AddBuffer(m_vb, m_layout);
    }

    TestTriangle::~TestTriangle()
    {
        m_shader.Unbind();
    }

    void TestTriangle::OnUpdate(float deltaTime)
    {
    }

    void TestTriangle::OnRender()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));

        m_va.Bind();
        m_shader.Bind();

        // 3 indices starting at 0 -> 1 triangle
        GLCall( glDrawArrays(GL_TRIANGLES, 0, 3) );
    }

    void TestTriangle::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
};
