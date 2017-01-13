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

namespace fj {
    template<typename T> class UtahTeapot;
}

template<typename T>
class fj::UtahTeapot
{
public:
    typedef std::array<float, 3> Position;
private:
    struct Data
    {
        std::vector<uint32_t> Indecies;
        std::vector<Position> Verticies;
    };
private:
    UtahTeapot() = default;
public:
    ~UtahTeapot() = default;
    
    static constexpr fj::UtahTeapot<T>::Data data();
    
    static bool savaToFile(const std::string& filename);
};

#endif /* utah_teapot_hpp */
