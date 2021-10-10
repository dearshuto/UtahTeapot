#ifndef UT_COMPILE_TIME_TEAPOT_H_
#define UT_COMPILE_TIME_TEAPOT_H_

#include <ut/detail/ut_UtahTeapotData.h>
#include <ut/utility.hpp>
#include <array>
#include <cstdint>

namespace ut
{

template<uint8_t T, uint8_t U>
class TUtahTeapot
{
public:
    TUtahTeapot(const TUtahTeapot& other) = default;
    TUtahTeapot(TUtahTeapot&& other) = default;
    ~TUtahTeapot() = default;

    static TUtahTeapot<T, U> Create() noexcept
    {
        return TUtahTeapot();
    }

    const auto& GetVertices() const noexcept {
        return m_Vertices;
    }

    const auto& GetIndices() const noexcept {
        return m_Indices;
    }

private:
    TUtahTeapot() = default;

private:
    std::array<fj::Vertex, 64> m_Vertices = {};
    std::array<uint32_t, 64> m_Indices = {]};
};

}

#endif