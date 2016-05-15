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

class TerrainLayer : public cocos2d::Node {
public:
    CREATE_FUNC(TerrainLayer);
    TerrainLayer()
    : ready( false ),
    distanceFactor( 0.f )
    {}
    bool init() override;
    //void onEnter() override;
    
    void initDistanceFactor( float distanceFactor ) {
        if ( distanceFactor < 0 ) {
            CCLOG( "invalid distance factor value, must be >= 0" );
            return;
        }
        distanceFactor = std::min<float>( distanceFactor, 1.f );
        this->distanceFactor = distanceFactor;
    }
    float getDistanceFactor() {
        return this->distanceFactor;
    }
    
    void step( float dt );
private:
    bool ready;
    TerrainGenerator generator;
    cocos2d::Node* nodeContainer;
    float distanceFactor; // 0 = camera plane, 1 = infinitely far
    
    std::deque<TerrainChunk*> terrainChunks;
    void handleCycling();
    void addNewTerrainChunk();
};

#endif /* TerrainLayer_hpp */
