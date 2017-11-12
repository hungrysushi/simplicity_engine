/*
 * unit tests for the Simplicity class
 */

#include "gtest/gtest.h"

#include "simplicity/simplicity.h"

namespace simplicity {

class SimplicityTests : public testing::Test {
protected:
        virtual void SetUp() {

        }

        virtual void TearDown() {

        }

        Simplicity engine;
};

// Tests the window creation
TEST_F(SimplicityTests, WindowCreation) {
        EXPECT_EQ(engine.window_, nullptr);

        EngineError error = engine.InitWindow(400, 400, "TestWindow");

        EXPECT_EQ(EngineError::kSuccess, error);
        EXPECT_NE(engine.window_, nullptr);
}
}  /* namespace simplicity */
