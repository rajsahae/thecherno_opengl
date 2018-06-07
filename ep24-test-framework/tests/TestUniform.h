#pragma once

#include "tests/Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

namespace test
{
    class TestUniform : public Test
    {
        public:
            TestUniform();
            ~TestUniform();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

        private:
            float m_ClearColor[4];
            float m_ObjectColor[4];
            float m_Positions[8];
            unsigned int m_Indices[6];
            float m_Step;
            int m_Direction;
            bool m_Oscillate;

            VertexArray m_va;
            IndexBuffer m_ib;
            VertexBuffer m_vb;
            VertexBufferLayout m_layout;
            Shader m_shader;
            Renderer m_renderer;
    };
    
}
