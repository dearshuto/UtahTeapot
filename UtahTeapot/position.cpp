//
//  position.cpp
//  utah_teapod
//
//  Created by Shuto Shikama on 2017/12/31.
//

#include "position.hpp"

fj::Position::Position(const float x, const float y, const float z)
: X(x), Y(y), Z(z)
{
    
}

fj::Position fj::Position::operator+(const fj::Position & position)const
{
    return fj::Position{X + position.X, Y + position.Y, Z + position.Z};
}

fj::Position operator*(const float n, const fj::Position& position)
{
    return fj::Position{n*position.X, n*position.Y, n*position.Z};
}
