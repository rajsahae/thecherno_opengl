#pragma once

#include "tests/Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    class TestMultipleObjects : public Test
    {
        public:
            TestMultipleObjects();
            ~TestMultipleObjects();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

        private:
            // data members
            float m_ClearColor[4];
            float m_Positions[16];
            unsigned int m_Indices[6];

            // opengl members
            VertexArray m_va;
            IndexBuffer m_ib;
            VertexBuffer m_vb;
            VertexBufferLayout m_layout;
            Shader m_shader;
            Texture m_texture;
            Renderer m_renderer;

            // MVP members
            glm::mat4 m_proj;
            glm::mat4 m_view;
            // model and mvp will be created per object per draw

            // Translation members
            glm::vec3 m_translationA;
            glm::vec3 m_translationB;
    };
    
}
