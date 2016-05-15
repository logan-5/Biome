//
//  SceneryLayer.hpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#ifndef SceneryLayer_hpp
#define SceneryLayer_hpp

#include "cocos2d.h"
#include <deque>
#include "TerrainLayer.hpp"
#include "ScrollingLayer.hpp"
class BiomeManager;

class SceneryNode;
class MainScene;

class SceneryLayer : public cocos2d::Node, public ScrollingLayer {
public:
    CREATE_FUNC(SceneryLayer);
    
    bool init() override;
    
    void initSizeX( float sizeX ) {
        if ( hasSetSizeX ) {
            CCLOG( "sizeX already set for scenery node!" );
            return;
        }
        this->sizeX = sizeX;
        hasSetSizeX = true;
        if ( hasSetNumberOfNodes ) {
            this->setUpSceneryNode();
        }
    }
    
    void initNumberOfNodes( int numberOfNodes ) {
        if ( hasSetNumberOfNodes ) {
            CCLOG( "numberOfNodes already set for scenery node!" );
            return;
        }
        this->numberOfNodes = numberOfNodes+1;
        hasSetNumberOfNodes = true;
        if ( hasSetSizeX ) {
            this->setUpSceneryNode();
        }
    }

    void initDistanceFactor( float distanceFactor) override {
        SceneryLayer::ScrollingLayer::initDistanceFactor( distanceFactor );
        if ( this->terrain ) this->terrain->initDistanceFactor( distanceFactor );
    }
    
    void setDensity( float density ) {
        this->density = cocos2d::clampf( density, 0.f, 1.f );
    }
    float getDensity() {
        return this->density;
    }
    void setSpriteScale( float spriteScale ) {
        this->spriteScale = spriteScale;
    }
    float getSpriteScale() {
        return this->spriteScale;
    }
    void setSpriteScaleVar( float spriteScaleVar ) {
        this->spriteScaleVar = spriteScaleVar;
    }
    float getSpriteScaleVar() {
        return this->spriteScaleVar;
    }
    void setScene( MainScene* scene ) {
        this->scene = scene;
    }
    void initTerrainLayer( TerrainLayer* t ) {
        this->terrain = t;
        t->initDistanceFactor( this->getDistanceFactor() );
        t->setLocalZOrder( this->getLocalZOrder() );
    }
    
    const BiomeManager& getBiomeManager();
    
    void step( float absDist ) override;
    
protected:
    std::deque<SceneryNode*> sceneryNodes;
    
private:
    MainScene* scene;
    int numberOfNodes;
    float sizeX;
    
    float density;
    float spriteScale, spriteScaleVar;
    bool hasSetNumberOfNodes, hasSetSizeX, ready;
    TerrainLayer* terrain;
    
    void setUpSceneryNode();
    void handleCycling( MoveDirection direction ) override;
    float getYPositionForNode( const SceneryNode& node, float xOffset = 0 );
};

#endif /* SceneryLayer_hpp */
