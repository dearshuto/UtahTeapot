//
//  main.cpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/02.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>
#include <ut/mesh_type.h>
#include <ut/utah_teapot.hpp>

int main(int argc, const char * argv[]) {
    
    ut::TUtahTeapot<64, 64> utahTeapod;
    utahTeapod.Reset(25, 25);

    std::ofstream output("utah_teapot_25x25.obj");
    
    for (const auto& kPosition : utahTeapod.GetVertices())
    {
        output << "v " << kPosition.Position.X << " " << kPosition.Position.Y << " " << kPosition.Position.Z << std::endl;
    }
    
    for (std::uint64_t i = 0; i < utahTeapod.GetIndices().size(); i += 4)
    {
        output << "f " << utahTeapod.GetIndices()[i+0] << " " << utahTeapod.GetIndices()[i+1] << " " << utahTeapod.GetIndices()[i+2] << " " << utahTeapod.GetIndices()[i+3] << std::endl;
    }    

    return 0;
}
