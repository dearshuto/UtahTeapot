//
//  position.hpp
//  utah_teapod
//
//  Created by Shuto Shikama on 2017/12/31.
//

#ifndef position_hpp
#define position_hpp

namespace fj {
    //! @brief 3 次元の位置情報です。
    class Position
    {
    public:
        Position() = default;
        Position(const fj::Position&) = default;
        Position(const float , const float y, const float z);
        virtual~Position() = default;

        inline fj::Position operator+(const fj::Position& position)const;
        inline fj::Position& operator+=(const fj::Position& other)
        {
            this->X += other.X;
            this->Y += other.Y;
            this->Z += other.Z;
            return *this;
        }
        
        float X;
        float Y;
        float Z;
    };
}

fj::Position operator*(const float n, const fj::Position& position);

#endif /* position_hpp */
