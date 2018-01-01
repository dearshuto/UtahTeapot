//
//  utah_teapot.hpp
//  UtahTeapot
//
//  Created by Shuto Shikama on 2016/12/02.
//  Copyright © 2016年 Shuto Shikama. All rights reserved.
//

#ifndef utah_teapot_hpp
#define utah_teapot_hpp

#include <string>
#include <vector>
#include "position.hpp"

namespace fj
{
    //! @brief ベジエ曲面の制御点から四角ポリゴンを抽出して構成されるユタティーポッド
    //! @detail 注ぎ口が x 軸, ふたが z 軸方向のモデルが生成されます。
    class UtahTeapot
    {
    private:
        struct Data
        {
            std::vector<uint32_t> Indecies;
            std::vector<fj::Position> Verticies;
        };
    public:
        UtahTeapot() = default;
        ~UtahTeapot() = default;
        
        //! メッシュデータを更新します。
        void update(const std::uint64_t div, const std::uint64_t subDiv);
        
        const  std::vector<fj::Position>& getVertices()const{return m_vertices;}
        
        const std::vector<std::uint64_t>& getIndices()const{return m_indices;}

    private:
        std::vector<fj::Position> m_vertices;
        std::vector<std::uint64_t> m_indices;
    };

}

#endif /* utah_teapot_hpp */
