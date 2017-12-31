//
//  position.cpp
//  utah_teapod
//
//  Created by Shuto Shikama on 2017/12/31.
//

#include "position.hpp"

//fj::Position::Position(const float x, const float y, const float z)
//: X(x)
//, Y(y)
//, Z(z)
//{
//    
//}
//
//fj::Position& fj::Position::operator=(const fj::Position & other)
//{
//    X = other.X;
//    Y = other.Y;
//    Z = other.Z;
//    return *this;
//}
//
//fj::Position& fj::Position::operator+(const fj::Position & position)
//{
//    X += position.X;
//    Y += position.Y;
//    Z += position.Z;
//    return *this;
//}

fj::Position& operator*(const float n, fj::Position& position)
{
    position.X *= n;
    position.Y *= n;
    position.Z *= n;
    return position;
}
