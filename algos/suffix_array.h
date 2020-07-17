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

#include <cstdint>  // int_16_t int_32_t
#include <cstring>
#include <vector>
#include <algorithm>

namespace rld {
namespace algos {

   template <class T>
   T const& clamp(T const& v, T const& lo, T const& hi) {
      return v < hi ? (v > lo ? v : lo) : hi;
   }

   /// rank must be always >0 ; enforced by assert()
   template <class T>
   auto rank(T v) {
      return v; //mapping is: x - 256 so we get negative ranks, must fix internally
      //return v+128; // works
      //return clamp(v - ' ', 0, 127);
   }

   template <class T>
   bool rank_compare(T l, T r) {
      return rank(l) < rank(r);
   }

   class SuffixArray {
     public:
      using T = char;
      // Idx is type of offset in string passed in to constructor
      using Idx = int32_t;

      SuffixArray(T const* txt_, T const* txtEnd_);
      SuffixArray(T const* txt_, Idx size);
      //TODO SuffixArray(T const* txt_);

      std::vector<Idx>::const_iterator lower_bound(T const* s) const;
      //TODO is it possible to use some better rank based search rather then bipartion

      //TODO
      auto begin() const { return m_suffixArr.begin(); }
      auto end() const { return m_suffixArr.end(); }
      auto rbegin() const { return m_suffixArr.rbegin(); }
      auto rend() const { return m_suffixArr.rend(); }
      auto suffixArrCmp() const {
         auto e =m_txt+std::strlen(m_txt);
         return [txt = this->m_txt, e](Idx l, Idx r) {
            //return std::strcmp(txt + l, txt + r) < 0;//TODO rank
            return std::lexicographical_compare(txt + l, e,
                                                txt + r, e,
                                                rank_compare<T>);
         };
      }

     private:
      std::vector<Idx> const m_suffixArr;
      T const* const m_txt;
   };

}  // namespace algos
}  // namespace rld
