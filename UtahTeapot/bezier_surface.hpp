//
//  bezier_surface.hpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/06.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#ifndef bezier_surface_hpp
#define bezier_surface_hpp

#include <array>
#include <cstdint>
#include <vector>
#include "position.hpp"

namespace fj {
    class BezierSurface;
}

class fj::BezierSurface
{
public:
    BezierSurface() = default;
    virtual~BezierSurface() = default;
    
    uint64_t execute();
    
    //! @brief バーンスタイン多項式 の値を算出します。
    //! @pre 0 ≦ t ≦ 1
    //! @pre 0 ≦ i ≦ 3
    static float ComputeBernsteinPolynormal(const float t, std::uint32_t i);
    
    /** 制御点を取得する */
    Position& ControllPoint(const uint8_t index)
    {
        return m_controllPoints[index];
    }
    
    const Position& getMeshVertex(const uint64_t index)
    {
        return m_vertices[index];
    }
    
    const std::vector<uint64_t>& getMeshInices()const
    {
        return m_indices;
    }
    
    //! @brief ベジエ曲面の横方向の分割数を返します。
    //! @detail 4 頂点の単純な四角形を描画するときは 0 を返します。
    std::uint64_t getDiv()const;

    //! @brief ベジエ曲面の縦方向の分割数を返します。
    //! @detail 4 頂点の単純な四角形を描画するときは 0 を返します。
    std::uint64_t getSubDiv()const;
    
private:
    
    /* 制御点の順番はこんな感じ
     0---1---2---3
     4---5---6---7
     8---9---10--11
     12--13--14--15
     */
    std::array<fj::Position, 16> m_controllPoints;

    //! @brief 横方向の分割数
    std::uint64_t m_DivN = 0;
    
    //! @brief 縦方向の分割数
    std::uint64_t m_DivM = 0;
    
    std::vector<uint64_t> m_indices;
    std::vector<fj::Position> m_vertices;
};

#endif /* bezier_surface_hpp */
