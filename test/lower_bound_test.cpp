#include <iostream>
#include <array>

#include "gtest/gtest.h"

#include "algos/utils.h" //TODO private header
#include "algos/lower_bound.h"

namespace algos { namespace {
  TEST(lowerbound, int_native_array)
  {
    int data[] = {
        1,        5,        7,        7,        7,        9,        9,        11,        22,        44,        666,        1000,
    };
    auto idx = [&](auto it) { return it - data; };
    EXPECT_EQ(idx(lower_bound(data, data + dim(data), 9)) , 5);
    EXPECT_EQ(idx(lower_bound(data, data + dim(data), 8)) , 5);
    EXPECT_EQ(idx(lower_bound(data, data + dim(data), 7)) , 2);
    EXPECT_EQ(idx(lower_bound(data, data + dim(data), 6)) , 2);
    EXPECT_EQ(idx(lower_bound(data, data + dim(data), 5)) , 1);
    EXPECT_EQ(idx(lower_bound(data, data + dim(data), 1)) , 0);
    EXPECT_EQ(idx(lower_bound(data, data + dim(data), 0)) , 0);
  }
  TEST(lowerbound, int_std_array)
  {
    std::array<char,10> data{ "ab" "defghij" }; data[9]='k';
    EXPECT_EQ(*algos::lower_bound(data.begin(), data.end(), 'd') , 'd');
    EXPECT_EQ(*algos::lower_bound(data.begin(), data.end(), 'c') , 'd');
  }
}} // namespace

#if 0
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
