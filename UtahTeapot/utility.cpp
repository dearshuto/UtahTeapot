//
//  utility.cpp
//  utah_teapod
//
//  Created by Shuto Shikama on 2017/12/31.
//

#include "utility.hpp"

std::uint64_t fj::Factrial(const std::uint64_t n)
{
    return (n == 0 || n == 1) ? 1 : n*Factrial(n-1);
}
