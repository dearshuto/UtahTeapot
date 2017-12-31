//
//  bezier_surface.cpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/06.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#include "mesh_type.h"
#include "bezier_surface.hpp"

template<class T>
uint64_t fj::BezierSurface<T>::execute()
{
    // 3次ベジエを求めるラムダ関数
    const auto computeBezier3 = [](const Position& p0, const Position& p1, const Position& p2, const Position& p3, const float t){
        Position vertex;
        for (int i = 0; i < vertex.size(); i++)
        {
            vertex[i] = (1-t)*(1-t)*(1-t)*p0[i] + 3*(1-t)*(1-t)*t*p1[i] + 3*(1-t)*t*t*p2[i] + t*t*t*p3[i];
        }
        return vertex;
    };
    
    m_indices.clear();
    m_vertices.clear();
    
    constexpr float kDiv = 50.0f;
    m_vertices.push_back(ControllPoint(0));
    for (std::uint32_t i = 0; i < 4; ++i)
    {
        for (float t = 0; t <= 1; t +=1.0f/kDiv)
        {
            const auto kPosition = computeBezier3(
                                                  ControllPoint(i*4+0)
                                                  , ControllPoint(i*4+1)
                                                  , ControllPoint(i*4+2)
                                                  , ControllPoint(i*4+3)
                                                  , t);
            m_vertices.push_back(kPosition);
        }
    }

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


template class fj::BezierSurface<TriangleMesh>;
template class fj::BezierSurface<SquareMesh>;
