//
//  bezier_surface.cpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/06.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#include "bezier_surface.hpp"
#include "mesh_type.h"
#include "utility.hpp"
#include <cassert>
#include <cmath>
#include <functional>

void fj::BezierSurface::update(const std::uint32_t div, std::uint32_t subDiv) {
  // ベジエ曲面上の UV 座標を表す構造体。
  // UV なので 値は [0, 1] の範囲です。
  struct BezierCoordinate {
    float U{0.0f};
    float V{0.0f};
  };

  // ベジエ曲面を消去
  m_indices.clear();
  m_vertices.clear();

  // たてよこの頂点数を取得。
  // 両端に頂点があるので +2 してます。
  const std::uint64_t kN = div + 2;
  const std::uint64_t kM = subDiv + 2;

  // 各頂点の UV 座標
  // i 番目の要素がが m_vertices[i] の UV を表します
  // UV はこの関数内でしか使わないので、頂点と UV で別変数を管理してます。
  std::vector<BezierCoordinate> uv;

  // 頂点数分の領域を確保
  uv.resize(kN * kM);
  m_vertices.resize(kN * kM);

  // ベジエ曲面上で隣り合う頂点の距離
  // 等分割を前提にしているので、すべて同じ感覚で並んでます。
  const float kStrideU = 1.0f / (div + 1);
  const float kStrideV = 1.0f / (subDiv + 1);

  // 求める頂点の UV 座標を算出。
  for (std::uint32_t n = 0; n < kN; ++n) {
    for (std::uint32_t m = 0; m < kM; ++m) {
      uv[n + kN * m].U = kStrideU * static_cast<float>(n);
      uv[n + kN * m].V = kStrideV * static_cast<float>(m);
    }
  }

  // 全頂点に対してベジエ曲面上の座標を算出
  for (std::uint32_t n = 0; n < kN; ++n) {
    for (std::uint32_t m = 0; m < kM; ++m) {
      const float kU = uv[n + kN * m].U;
      const float kV = uv[n + kN * m].V;

      // 足しこみを行うので 全ての要素を 0 で初期化しておく
      fj::Vertex &position = m_vertices[n + m * kN];
      position.Position = fj::Vector{0.0f, 0.0f, 0.0f};

      // ずべての制御点からの影響を足しこむ
      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
          const fj::Vector &kControlPoint = getControllPoint(i + 4 * j);
          const float kBu = ComputeBernsteinPolynormal(kU, i);
          const float kBv = ComputeBernsteinPolynormal(kV, j);
          position.Position += kBu * kBv * kControlPoint;
        }
      }
    }
  }

  // 四角ポリゴンとして登録。
  for (std::uint32_t n = 0; n < kN - 1; ++n) {
    for (std::uint32_t m = 0; m < kM - 1; ++m) {
      const int kLeftUp = n + m * kN;
      m_indices.push_back(kLeftUp);
      m_indices.push_back(kLeftUp + 1);
      m_indices.push_back(kLeftUp + kN + 1);
      m_indices.push_back(kLeftUp + kN);
    }
  }
}

float fj::BezierSurface::ComputeBernsteinPolynormal(const float t,
                                                    std::uint32_t i) {
  assert(0 <= t && t <= 1);
  assert(0 <= i && i <= 3); // 3次なので

  // 3 次バーンスタイン多項式
  constexpr std::uint64_t n = 3; // 3次なので

  // 二項係数
  const float kBinomialCoefficients =
      fj::Factrial(n) / (fj::Factrial(i) * fj::Factrial(n - i));

  return kBinomialCoefficients * std::pow(t, i) *
         std::pow<float>(1.0f - t, n - i);
}
