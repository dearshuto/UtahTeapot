//
//  utah_teapot.hpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/02.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#ifndef utah_teapot_hpp
#define utah_teapot_hpp

#include <array>
#include <string>
#include <vector>
#include "position.hpp"

namespace fj
{
    class UtahTeapot
    {
    private:
        struct Data
        {
            std::vector<uint32_t> Indecies;
            std::vector<fj::Position> Verticies;
        };
    private:
        UtahTeapot() = default;
    public:
        ~UtahTeapot() = default;
        
        static fj::UtahTeapot::Data data();
        
        static bool savaToFile(const std::string& filename);

        //! @param[in] div 横方向の分割数
        //! @param[in] subDiv 縦方向の分割数
        static bool savaToFile(const std::string& filename, const std::uint64_t div, const std::uint64_t subDiv);
    };

}

#endif /* utah_teapot_hpp */
