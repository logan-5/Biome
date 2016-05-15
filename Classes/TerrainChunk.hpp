//
//  TerrainChunk.hpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#ifndef TerrainChunk_hpp
#define TerrainChunk_hpp

#include "cocos2d.h"

class TerrainChunk : public cocos2d::Layer {
public:
    friend class TerrainGenerator;
    CREATE_FUNC(TerrainChunk);
    bool init() override;
    
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    float getHeightForAbsoluteXCoordinate( float x );
private:
    std::vector<cocos2d::Vec2> points;
    cocos2d::CustomCommand _customCmd;
    void onDraw( const cocos2d::Mat4 &transform, uint32_t flags);
    
    cocos2d::Color4F _DEBUGGING_ONLY_lineColor;
};

#endif /* TerrainChunk_hpp */
