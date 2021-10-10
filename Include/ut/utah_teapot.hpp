//
//  utah_teapot.hpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/02.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#ifndef utah_teapot_hpp
#define utah_teapot_hpp

#include <ut/detail/bezier_surface.hpp>
#include "utility.hpp"
#include <array>
#include <string>
#include <vector>

namespace ut { namespace detail {
  void Setup(fj::Vertex* pVertices, int32_t vertexCount, uint32_t* pIndices, int32_t indexCount, int32_t divX, int32_t divY) noexcept;
}}

namespace ut {

//! @todo ヒープを使わない実装
//!
template<uint8_t DivMax, uint8_t SubDivMax>
class TUtahTeapot
{
public:
  TUtahTeapot() noexcept
    : TUtahTeapot(0, 0)
  {

  }

  TUtahTeapot(uint8_t divX, uint8_t divY) noexcept
  {
      Reset(divX, divY);
  }

  void Reset(uint8_t divX, uint8_t divY) noexcept
  {
      detail::Setup(
        m_Vertices.data(), 
        static_cast<int32_t>(m_Vertices.size()),
        m_Indices.data(),
        static_cast<int32_t>(m_Indices.size()),
        divX,
        divY);
  }

  const auto& GetVertices() const noexcept
  {
      return m_Vertices;
  }

  const auto& GetIndices() const noexcept
  {
      return m_Indices;
  }

private:
    std::array<fj::Vertex, 64> m_Vertices;
    std::array<std::uint32_t, 64> m_Indices;
};

}

#endif /* utah_teapot_hpp */
