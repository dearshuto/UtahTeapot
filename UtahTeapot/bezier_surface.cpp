//
//  bezier_surface.cpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/06.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#include <cassert>
#include <cmath>
#include <functional>
#include "mesh_type.h"
#include "utility.hpp"
#include "bezier_surface.hpp"

uint64_t fj::BezierSurface::execute()
{
    //! ベジエ曲面上の UV 座標を表す構造体。
    struct BezierCoordinate
    {
        float U{0.0f}; // 無効な値で初期化
        float V{0.0f}; // 無効な値で初期化
    };
    
    // ベジエ曲面を消去
    m_indices.clear();
    m_vertices.clear();

   // たてよこの分割数を取得。
    // 両端に頂点があるので +2 してます。
    const std::uint64_t kN = getDiv() + 2;
    const std::uint64_t kM = getSubDiv() + 2;
    std::vector<BezierCoordinate> uv;
    
    // 頂点数分の領域を確保
    uv.resize(kN * kM);
    m_vertices.resize(kN * kM);
    
    // ベジエ曲面上で隣り合う頂点の距離
    // 等分割を前提にしているので、すべて同じ感覚で並んでます。
    const float kStrideU = 1.0f / (getDiv()+1);
    const float kStrideV = 1.0f / (getSubDiv()+1);
    
    // 求める頂点の UV 座標を算出。
    for (std::uint32_t n = 0; n < kN; ++n) {
        for (std::uint32_t m = 0; m < kM; ++m)
        {
            uv[n + kN*m].U = kStrideU * static_cast<float>(n);
            uv[n + kN*m].V = kStrideV * static_cast<float>(m);
        }
    }

    // ベジエ曲面上の座標を算出
    for (std::uint32_t n = 0; n < kN; ++n) {
        for (std::uint32_t m = 0; m < kM; ++m)
        {
            Position& position = m_vertices[n+m*kN];
            const float kU = uv[n + kN*m].U;
            const float kV = uv[n + kN*m].V;
            // ずべての制御点からの影響を足しこむ
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j)
                {
                    const fj::Position& kControlPoint = ControllPoint(i + 4*j);
                    const float kBu = ComputeBernsteinPolynormal(kU, i);
                    const float kBv = ComputeBernsteinPolynormal(kV, j);
                    position += kBu * kBv * kControlPoint;
                }
            }
        }
    }
    
    for (std::uint32_t n = 0; n < kN-1; ++n){
        for (std::uint32_t m = 0; m <kM-1; ++m)
        {
            const int kLeftUp = n + m*kN;
            m_indices.push_back(kLeftUp);
            m_indices.push_back(kLeftUp+1);
            m_indices.push_back(kLeftUp + kN + 1);
            m_indices.push_back(kLeftUp + kN);
        }
    }
    
    return 1;
}

float fj::BezierSurface::ComputeBernsteinPolynormal(const float t, std::uint32_t i )
{
    assert(0 <= t && t <= 1);
    assert(0 <= i && i <= 3); // 3次なので
    
    // 3 次バーンスタイン多項式
    constexpr std::uint64_t n = 3; // 3次なので
    
    // 二項係数
    const float kBinomialCoefficients =  fj::Factrial(n) / (fj::Factrial(i)*fj::Factrial(n-i));
    
    return kBinomialCoefficients * std::pow(t, i) * std::pow<float>(1.0f-t, n-i);
}

std::uint64_t fj::BezierSurface::getDiv()const
{
    return m_Div;
}

void fj::BezierSurface::setDiv(const std::uint64_t div)
{
    m_Div = div;
}

std::uint64_t fj::BezierSurface::getSubDiv()const
{
    return m_SubDiv;
}

void fj::BezierSurface::setSubDiv(const std::uint64_t subDiv)
{
    m_SubDiv = subDiv;
}
