/*
* Algos library
*
* Copyright Rafal Dzbek 2020
*
*  Use, modification and distribution is subject to the
*  Boost Software License, Version 1.0. (See accompanying
*  file LICENSE_1_0.txt or copy at
*  http://www.boost.org/LICENSE_1_0.txt)
*
* Project home: https://
*/

#pragma once

// return it to elem which is not less than (i.e. greater or equal to) value, or last if no such element is found.
//      insert position
template <class RandomIt, class T>
RandomIt
lower_bound(RandomIt f, RandomIt l, T val)
{
    while(f != l) {
        auto m = f + (l-f)/2;
        if(*m<val) f=m+1; 
        else l=m;
    }
    return f;
}
