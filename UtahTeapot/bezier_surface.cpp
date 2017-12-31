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
        float U{-1.0f}; // 無効な値で初期化
        float V{-1.0f}; // 無効な値で初期化
    };
    
    // ベジエ曲面を消去
    m_indices.clear();
    m_vertices.clear();

    const std::uint64_t kN = getDiv();
    const std::uint64_t kM = getSubDiv();
    std::vector<BezierCoordinate> uv;
    uv.resize(kN*kM);
    m_vertices.resize(kN* kM);
    
    // 1. ベジエ曲面上の座標を計算
    // まずはすべての UV を (0, 0) で初期化
//    std::fill(std::begin(uv), std::end(uv)
//              , [](BezierCoordinate& uv)
//              {
//                  uv.U = 0.0f;
//                  uv.V = 0.0f;
//              });
    
    const float kStrideU = 1.0f / (kN+1);
    const float kStrideV = 1.0f / (kM+1);
    for (std::uint32_t n = 0; n < kN; ++n) {
        for (std::uint32_t m = 0; m < kM; ++m)
        {
            uv[n + kN*m].U = kStrideU * static_cast<float>(n);
            uv[n + kN*m].V = kStrideV * static_cast<float>(m);
        }
    }

    // 2. ベジエ曲面上の座標を算出
    for (std::uint32_t n = 0; n < kN; ++n) {
        for (std::uint32_t m = 0; m < kM; ++m)
        {
            Position& position = m_vertices[n+m];
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j)
                {
                    const float kBu = 1.0f;
                    const float kBv = 1.0f;                
                }
            }

        }
    }
    
    constexpr float kDiv = 50.0f;
    
    
    m_vertices.push_back(ControllPoint(0));

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < static_cast<int>(kDiv); ++j)
        {
            const int kStride = (static_cast<int>(kDiv)+1);
            const int kLeftUp = i*kStride + j;
            const int kLeftDown = kLeftUp + kStride;
            m_indices.push_back(kLeftUp);
            m_indices.push_back(kLeftUp+1);
            m_indices.push_back(kLeftDown + 1);
            m_indices.push_back(kLeftDown);
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
    
    return kBinomialCoefficients * std::pow<float>(1.0f-t, n-i);
}

std::uint64_t fj::BezierSurface::getDiv()const
{
    return m_DivN;
}

std::uint64_t fj::BezierSurface::getSubDiv()const
{
    return m_DivM;
}
