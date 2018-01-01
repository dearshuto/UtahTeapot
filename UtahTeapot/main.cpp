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
#include "mesh_type.h"
#include "utah_teapot.hpp"
#include "bezier_surface.hpp"
#include "utility.hpp"

int main(int argc, const char * argv[]) {
    
    fj::UtahTeapot utahTeapod;
    utahTeapod.update(25, 25);

    std::ofstream output("utah_teapot_25x25.obj");
    
    for (const auto& kPosition : utahTeapod.getVertices())
    {
        output << "v " << kPosition.Position.X << " " << kPosition.Position.Y << " " << kPosition.Position.Z << std::endl;
    }
    
    for (std::uint64_t i = 0; i < utahTeapod.getIndices().size(); i += 4)
    {
        output << "f " << utahTeapod.getIndices()[i+0] << " " << utahTeapod.getIndices()[i+1] << " " << utahTeapod.getIndices()[i+2] << " " << utahTeapod.getIndices()[i+3] << std::endl;
    }
    
    return 0;
}
