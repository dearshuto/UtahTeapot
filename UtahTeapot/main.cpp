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

int main(int argc, const char * argv[]) {
    fj::BezierSurface<SquareMesh> bezie;
    bezie.ControllPoint(0) = {{0.0f, 1.0f, 0.0f}};
    bezie.ControllPoint(1) = {{1.0f, 1.0f, 0.0f}};
    bezie.ControllPoint(2) = {{0.0f, 0.0f, 0.0f}};
    bezie.ControllPoint(3) = {{1.0f, 0.0f, 0.0f}};
    bezie.execute();

    std::ofstream input("test.obj");
    
    
    const auto meshData = fj::UtahTeapot<SquareMesh>::data();
    fj::UtahTeapot<SquareMesh>::savaToFile("test.obj");
    
    return 0;
}
