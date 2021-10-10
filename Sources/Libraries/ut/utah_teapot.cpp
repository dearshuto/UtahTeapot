//
//  utah_teapot.cpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/02.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#include <ut/detail/bezier_surface.hpp>
#include <ut/detail/ut_UtahTeapotData.h>
#include <ut/utah_teapot.hpp>
#include <ut/utah_teapot.hpp>
#include <ut/utility.hpp>
#include <array>
#include <fstream>
#include <functional>

void fj::UtahTeapot::update(const std::uint64_t div,
                            const std::uint64_t subDiv) {
  int indexStride = 0;
  for (const ut::detail::Bezier16IndicesArray &bezierIndiices : ut::detail::g_indices) {
    fj::BezierSurface bezier;
    for (int i = 0; i < bezierIndiices.size(); i++) {
      const auto &kVertex = ut::detail::g_vertices[bezierIndiices[i] - 1];
      bezier.getControllPoint(i) =
          fj::Vector{kVertex[0], kVertex[1], kVertex[2]};
    }

    bezier.update(div, subDiv);

    for (const auto &index : bezier.getMeshInices()) {
      const auto kVertex = bezier.getMeshVertex(index);
      m_vertices.push_back(kVertex);
    }

    const std::vector<uint64_t> &kIndeces = bezier.getMeshInices();
    for (std::uint64_t i = 0; i < kIndeces.size(); i += 4) {
      m_indices.push_back(indexStride + i + 1);
      m_indices.push_back(indexStride + i + 2);
      m_indices.push_back(indexStride + i + 3);
      m_indices.push_back(indexStride + i + 4);
    }
    indexStride += kIndeces.size();
  }
}
