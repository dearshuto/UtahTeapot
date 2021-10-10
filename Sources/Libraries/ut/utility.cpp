//
//  utility.cpp
//  utah_teapod
//
//  Created by Shuto Shikama on 2017/12/31.
//

#include "utility.hpp"

std::uint64_t fj::Factrial(const std::uint64_t n) {
  return (n == 0 || n == 1) ? 1 : n * Factrial(n - 1);
}

fj::Vector::Vector(const float x, const float y, const float z)
    : X(x), Y(y), Z(z) {}

fj::Vector fj::Vector::operator+(const fj::Vector &vector) const {
  return fj::Vector{this->X + vector.X, this->Y + vector.Y, this->Z + vector.Z};
}
