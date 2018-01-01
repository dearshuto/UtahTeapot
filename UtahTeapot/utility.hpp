//
//  utility.hpp
//  utah_teapod
//
//  Created by Shuto Shikama on 2017/12/31.
//

#ifndef utility_hpp
#define utility_hpp

#include <cstdint>

namespace fj{
        
    //! @brief n の階乗を求めます。
    //! @param[in] n 階乗を求めたい整数。
    //! @pre n! の計算結果が std::uint64_t でオーバーフローが発生しない値
    std::uint64_t Factrial(const std::uint64_t n);
}

#endif /* utility_hpp */
