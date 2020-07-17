#include <iostream>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "algos/topo_sort.h"

namespace {
BOOST_AUTO_TEST_CASE(test) {
  //std::unordered_multimap< int, int> adj = { 
  std::multimap< int, int> adj = { 
    {0,7},
    {1,6}, 
    {2,5}, 
    {3,5}, 
    {4,5}, 
    {5,6}, 
    {4,7}, 
    {6,7}, 
    {7,8}, 
    {9,7},
    };
  auto r = topo_sort(adj);
  std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 9, 7, 8,};
  BOOST_CHECK_EQUAL_COLLECTIONS(r.begin(),r.end(), expected.begin(),expected.end());
}
}
