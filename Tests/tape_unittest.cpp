#include <gtest/gtest.h>

#include "tape.h"

int main(int argc, char *argv[]){
    printf(" init GTest ");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(someTest, testOne){
  ASSERT_EQ(5, 5);
}
