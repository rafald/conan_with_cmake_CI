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

template< typename T, size_t N >
inline size_t dim( T (&arr)[N] ) { return N; }
