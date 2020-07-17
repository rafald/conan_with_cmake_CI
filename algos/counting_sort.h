/*
* Algos library
*
* Copyright Rafal Dzbek 2017
*
*  Use, modification and distribution is subject to the
*  Boost Software License, Version 1.0. (See accompanying
*  file LICENSE_1_0.txt or copy at
*  http://www.boost.org/LICENSE_1_0.txt)
*
* Project home: https://
*/

#pragma once

#include <algorithm>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>  //partial_sum
#include <type_traits>
#include <utility>
#include <vector>

namespace rld {
namespace algos {
   namespace detail {
      template <class T>
      using naked_type = typename std::remove_reference<typename std::remove_cv<T>::type>::type;

      template <class MutableForwardIt>
      using ValueTypeFromIt = naked_type<decltype(*std::declval<MutableForwardIt>())>;
   }  // namespace detail

   // default ranking is: id :: a -> a
   template <class T>
   struct DefaultRanking {
      template <class RankType = T>
      RankType operator()(T t) const {
         return t;
      }
   };
   // specialize for char:  rank :: char -> unsigned char
   template <>
   struct DefaultRanking<char> {
      unsigned char operator()(char t) const { return t; }
   };
   template <>
   struct DefaultRanking<int> {
      unsigned int operator()(int t) const { return t; }
   };

   // int is used for 3rd arg max_range_value because on moderate machine there is OOM for int
   // rank_range_max == 0 use maximum range
   // rank_range_max < 0 scan input range to find max value
   // otherwise use supplied value
   // 4th in arg is custom ranking, can be lambda
   //
   // Note that std::numeric_limits<RankType>::max() does not have a slot
   // for max() value because first slot is for 0 value
   //
   // not online, not stable, not very much paralizable - only first step - make histogram - is amendable for paralisation
   template <class MutableForwardIt, class Ranking = DefaultRanking<detail::ValueTypeFromIt<MutableForwardIt>>>
   void counting_sort(MutableForwardIt first, MutableForwardIt last, int max_range_value = {}, Ranking rank = {}) {
      if (first == last) return;
      using ValueType = detail::naked_type<decltype(*std::declval<MutableForwardIt>())>;
      using RankType = detail::naked_type<decltype(rank(*std::declval<MutableForwardIt>()))>;

      // only unsigned type can be RankType
      static_assert(std::numeric_limits<RankType>::min() >= 0, "");

      if (not max_range_value) {
         // this does not handle max() value /one slot for 0/ !
         max_range_value = std::numeric_limits<RankType>::max();
      } else if (max_range_value < 0) {
         max_range_value = *std::max_element(first, last, [&rank](auto l, auto r) { return rank(l) < rank(r); });
         max_range_value += 1;  // for 0
      } else {
         ++max_range_value;  // for 0
      }
      std::vector<RankType> counts(max_range_value);

      // make histogram
      std::for_each(first, last, [&](ValueType value) { ++counts.at(rank(value)); });

      // alter to contain actual final position
      std::partial_sum(counts.begin(), counts.end(), counts.begin());

      // can not generate out seq inplace - build the output in separate space
      std::vector<ValueType> o(std::distance(first, last));
      std::for_each(first, last, [&](ValueType& value) {
         auto final_pos = counts.at(rank(value)) - 1;
         o[final_pos] = value;
         --counts.at(rank(value));  // nonunique values are populated backwards
      });

      // if in arg is vector then optimisation possible - swap vectors
      std::copy(o.begin(), o.end(), first);
   }
}  // namespace algos
}  // namespace rld
