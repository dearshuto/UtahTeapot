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
    const auto meshData = fj::UtahTeapot::data();
    fj::UtahTeapot::savaToFile("test.obj", 0, 0);
    fj::UtahTeapot::savaToFile("test_0x25.obj", 0, 25);
    fj::UtahTeapot::savaToFile("test_25x0.obj", 25, 0);
    fj::UtahTeapot::savaToFile("test_50x50.obj", 50, 50);
    
    return 0;
}
