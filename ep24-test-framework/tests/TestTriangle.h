#pragma once

#include "tests/Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

namespace test
{
    class TestTriangle : public Test
    {
        public:
            TestTriangle();
            ~TestTriangle();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

        private:
            float m_ClearColor[4];
            float m_Positions[6];

            VertexArray m_va;
            VertexBuffer m_vb;
            VertexBufferLayout m_layout;
            Shader m_shader;
    };
}
