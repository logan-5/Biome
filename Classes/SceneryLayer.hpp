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
class BiomeManager;

enum class MoveDirection {
    Forward,
    Backward,
};

class SceneryNode;
class MainScene;

class SceneryLayer : public cocos2d::Node {
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
    
    const BiomeManager& getBiomeManager();
    
    void step( float absDist );
    
protected:
    std::deque<SceneryNode*> sceneryNodes;
    
private:
    MainScene* scene;
    cocos2d::Node* nodeContainer;
    int numberOfNodes;
    float sizeX;
    float distanceFactor; // 0 = camera plane, 1 = infinitely far
    float density;
    float spriteScale, spriteScaleVar;
    bool hasSetNumberOfNodes, hasSetSizeX, ready;
    
    void setUpSceneryNode();
    void handleCycling( MoveDirection direction );
};

#endif /* SceneryLayer_hpp */
