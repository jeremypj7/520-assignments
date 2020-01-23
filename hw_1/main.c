#include <stdio.h>
#include "fraction.h"
#include "gtest/gtest.h"
#include "imaginary.h"

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
