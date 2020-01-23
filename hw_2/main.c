#include <stdio.h>
#include <stdlib.h>
#include "solutions.h"
#include "gtest/gtest.h"
#include <float.h>

GTEST_API_ int main(int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}