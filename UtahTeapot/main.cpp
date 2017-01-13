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

int main(int argc, const char * argv[]) {
//    std::ifstream input("teapot");
//    std::ofstream output("utahteapot_split");
//    std::string line;
//    while (std::getline(input, line))
//    {
//        output << "{" << line << "}," << std::endl;
//    }
    
    const auto meshData = fj::UtahTeapot<SquareMesh>::data();
    fj::UtahTeapot<SquareMesh>::savaToFile("test.obj");
    
    return 0;
}
