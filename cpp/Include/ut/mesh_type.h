//
//  mesh_type.h
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/06.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#ifndef mesh_type_h
#define mesh_type_h

#include <cstdint>

struct SquareMesh {
  static const uint8_t VertexNumPerMesh = 4;
};
struct TriangleMesh {
  static const uint8_t VertexNumPerMesh = 4;
};

#endif /* mesh_type_h */
