//
//  TerrainLayer.hpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#ifndef TerrainLayer_hpp
#define TerrainLayer_hpp

#include "cocos2d.h"
#include <deque>
#include "TerrainChunk.hpp"
#include "TerrainGenerator.hpp"
#include "ScrollingLayer.hpp"

class TerrainLayer : public cocos2d::Node, public ScrollingLayer {
public:
    CREATE_FUNC(TerrainLayer);
    TerrainLayer()
    : ready( false ),
    distanceFactor( 0.f )
    {}
    bool init() override;
    //void onEnter() override;

    float getHeightForScreenXCoordinate( float x );
    
    void step( float dt ) override;
private:
    bool ready;
    TerrainGenerator generator;
    float distanceFactor; // 0 = camera plane, 1 = infinitely far
    
    std::deque<TerrainChunk*> terrainChunks;
    void handleCycling( ScrollingLayer::MoveDirection moveDirection ) override;
    void addNewTerrainChunk();
};

#endif /* TerrainLayer_hpp */
