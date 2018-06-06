#pragma once

#include "tests/Test.h"


namespace test
{
    class TestClearColor : public Test
    {
        public:
            TestClearColor();
            ~TestClearColor();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

        private:
            float m_ClearColor[4];
    };
};
