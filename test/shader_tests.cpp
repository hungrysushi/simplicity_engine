/*
 * unit tests for the Shader class
 */

#include "gtest/gtest.h"

#include "renderer/shader.h"

#include "simplicity/simplicity.h"

namespace simplicity {

class ShaderTests : public testing::Test {
protected:
        virtual void SetUp() {

        }

        virtual void TearDown() {

        }

        Shader shader;
        
        // this isn't ideal, but we need the engine for InitWindow
        Simplicity engine;
};

// Test the Shader initialize function
TEST_F(ShaderTests, Initialization) {

        engine.InitWindow(100, 100, "TestShader");
        
        ShaderError error = shader.Initialize("../../shaders/basic.vs", "../../shaders/basic.fs");

        EXPECT_EQ(ShaderError::kSuccess, error);
}
}  // namespace simplicity
