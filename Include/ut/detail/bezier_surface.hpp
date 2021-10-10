//
//  bezier_surface.hpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/06.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#ifndef bezier_surface_hpp
#define bezier_surface_hpp

#include <ut/utility.hpp>
#include <array>
#include <cstdint>
#include <vector>

namespace fj {
class BezierSurface;
}

//! @brief 16 個の制御点から生成される 3 次ベジエ曲面
//! @brief 生成されるメッシュデータは四角ポリゴンで構成されています。
class fj::BezierSurface {
public:
  BezierSurface() = default;
  virtual ~BezierSurface() = default;

  //! @brief ベジエ曲面の分割数を更新します。
  //! @detail 分割数を 0 で更新すると四角メッシュを生成します。
  //! @param[in] div 横方向の分割数
  //! @param[in] subDiv 縦方向の分割数
  //! @note 分割数の限界は未確認です。どこかでオーバーフローが発生します。
  void update(const std::uint32_t div, std::uint32_t subDiv);

  //! @brief バーンスタイン多項式 の値を算出します。
  //! @pre 0 ≦ t ≦ 1
  //! @pre 0 ≦ i ≦ 3
  static float ComputeBernsteinPolynormal(const float t, std::uint32_t i);

  //! @brief制御点を取得します。
  //! @detail
  //! 制御点と UV 座標の関係は以下。
  //! uv は [0, 1] の値をとります。
  //!   → u
  //! ↓  0---1---2---3
  //! v  4---5---6---7
  //!    8---9---10--11
  //!    12--13--14--15
  Vector &getControllPoint(const uint8_t index) {
    return m_controllPoints[index];
  }

  const Vertex &getMeshVertex(const uint64_t index) {
    return m_vertices[index];
  }

  const std::vector<uint64_t> &getMeshInices() const { return m_indices; }

private:
  /* 制御点の順番はこんな感じ
   0---1---2---3
   4---5---6---7
   8---9---10--11
   12--13--14--15
   */
  std::array<Vector, 16> m_controllPoints;

  std::vector<uint64_t> m_indices;
  std::vector<Vertex> m_vertices;
};

namespace ut {namespace detail {

template<uint8_t MaxDivX, uint8_t MaxDivY>
class TBezierSurface
{
public:
  //! @brief バーンスタイン多項式 の値を算出します。
  //! @pre 0 ≦ t ≦ 1
  //! @pre 0 ≦ i ≦ 3
  static float ComputeBernsteinPolynormal(const float t, std::uint32_t i);

  //! @brief ベジエ曲面の分割数を更新します。
  //! @detail 分割数を 0 で更新すると四角メッシュを生成します。
  //! @param[in] div 横方向の分割数
  //! @param[in] subDiv 縦方向の分割数
  //! @note 分割数の限界は未確認です。どこかでオーバーフローが発生します。
  void update(const std::uint32_t div, std::uint32_t subDiv);

  //! @brief制御点を取得します。
  //! @detail
  //! 制御点と UV 座標の関係は以下。
  //! uv は [0, 1] の値をとります。
  //!   → u
  //! ↓  0---1---2---3
  //! v  4---5---6---7
  //!    8---9---10--11
  //!    12--13--14--15
  fj::Vector& GetControllPoint(const uint8_t index) noexcept
  {
    return m_ControllPoints[index];
  }

  const auto& GetVertices() const noexcept 
  {
      return &m_Vertices;
  }

  const auto& GetIndices() const noexcept   
  {
      return m_Indices; 
  }

private:
  /* 制御点の順番はこんな感じ
   0---1---2---3
   4---5---6---7
   8---9---10--11
   12--13--14--15
   */
  std::array<fj::Vector, 16> m_ControllPoints = {};

  std::array<uint32_t, 64> m_Indices = {};
  std::array<fj::Vertex, 64> m_Vertices = {};
};

}}

#endif /* bezier_surface_hpp */
