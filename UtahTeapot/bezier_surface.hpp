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

namespace fj {
    template<typename T> class BezierSurface;
}

class SquareMesh;
class TriangleMesh;

template<typename T>
class fj::BezierSurface
{
    typedef std::array<float, 3> Position;
public:
    BezierSurface() = default;
    virtual~BezierSurface() = default;
    
    uint64_t execute();
    
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
    
private:
    
    /* 制御点の順番はこんな感じ
     0---1---2---3
     4---5---6---7
     8--9--10--11
     12-13--14-15
     */
    std::array<Position, 16> m_controllPoints;
    
    std::vector<uint64_t> m_indices;
    std::vector<Position> m_vertices;
};

#endif /* bezier_surface_hpp */
