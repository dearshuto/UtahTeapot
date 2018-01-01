//
//  utility.hpp
//  utah_teapod
//
//  Created by Shuto Shikama on 2017/12/31.
//

#ifndef utility_hpp
#define utility_hpp

#include <cstdint>

namespace fj{
        
    //! @brief n の階乗を求めます。
    //! @param[in] n 階乗を求めたい整数。
    //! @pre n! の計算結果が std::uint64_t でオーバーフローが発生しない値
    std::uint64_t Factrial(const std::uint64_t n);
    
    //! @brief float 型 3 次元ベクトル
    //! @detail デフォルトですべての要素が 0 で初期化されています。
    //! @note 最低限の演算機能しかサポートしていません。
    class Vector
    {
    public:
        Vector() = default;
        ~Vector() = default;
       
        Vector(const float x, const float y, const float z);
        
        inline fj::Vector operator*(const float n)const
        {
            return fj::Vector{
                this->X*n
                , this->Y*n
                , this->Z*n};
        }
        
        inline fj::Vector operator+(const fj::Vector& vector)const;
        inline fj::Vector& operator+=(const fj::Vector& vector)
        {
            this->X += vector.X;
            this->Y += vector.Y;
            this->Z += vector.Z;
            return *this;
        }

        
        float X{0.0f};
        float Y{0.0f};
        float Z{0.0f};
    };
    
    //! 頂点座標と頂点法線
    struct Vertex
    {
    public:
        fj::Vector Position{0.0f, 0.0f, 0.0f};
        fj::Vector Normal;
    };
}

// 数字 * fj::Vector の演算子
inline fj::Vector operator*(const float n, const fj::Vector& vector)
{
    return fj::Vector{vector*n};
}

#endif /* utility_hpp */
