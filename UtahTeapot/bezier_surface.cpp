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
    T::VertexNumPerMesh;
    m_indices = {0, 1, 2, 3};
    m_vertices.push_back(ControllPoint(0));
    m_vertices.push_back(ControllPoint(3));
    m_vertices.push_back(ControllPoint(15));
    m_vertices.push_back(ControllPoint(12));
    
    return 1;
}


template class fj::BezierSurface<TriangleMesh>;
template class fj::BezierSurface<SquareMesh>;
