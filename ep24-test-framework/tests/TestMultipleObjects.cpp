#include "tests/TestMultipleObjects.h"

#include "Debug.h"
#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    TestMultipleObjects::TestMultipleObjects() :
        m_ClearColor { 0.8f, 0.3f, 0.2f, 1.0f },
        m_Positions {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 1.0f  // 3
        },
        m_Indices {
            0, 1, 2,
            2, 3, 0
        },
        m_va(),
        m_ib(m_Indices, 6),
        m_vb(m_Positions, 4 * 4 * sizeof(float)),
        m_layout(),
        m_shader("res/shaders/Complex.shader"),
        m_texture("res/textures/phone.png"),
        m_renderer(),
        m_proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_translationA(200, 200, 0),
        m_translationB(400, 200, 0)
    {
        m_layout.AddFloat(2);
        m_layout.AddFloat(2);
        m_va.AddBuffer(m_vb, m_layout);

        m_texture.Bind();
        m_shader.SetUniform1i("u_Texture", 0);
    }

    TestMultipleObjects::~TestMultipleObjects()
    {
        m_va.Unbind();
        m_shader.Unbind();
    }

    void TestMultipleObjects::OnUpdate(float deltaTime)
    {
    }

    void TestMultipleObjects::OnRender()
    {
        m_renderer.Clear();
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationA);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader.Bind();
            m_shader.SetUniformMat4f("u_MVP", mvp);
            m_renderer.Draw(m_va, m_ib, m_shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
            glm::mat4 mvp = m_proj * m_view * model;
            m_shader.Bind();
            m_shader.SetUniformMat4f("u_MVP", mvp);
            m_renderer.Draw(m_va, m_ib, m_shader);
        }
    }

    void TestMultipleObjects::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
        ImGui::SliderFloat3("TranslationA", &m_translationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("TranslationB", &m_translationB.x, 0.0f, 960.0f);
    }
};
