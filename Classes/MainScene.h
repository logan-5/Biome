#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SceneryLayer.hpp"
#include "TerrainLayer.hpp"
#include "BiomeManager.hpp"

#include <memory>

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    void update( float dt ) override;

    const BiomeManager& getBiomeManager() {
        return *biomeManager;
    }
private:
    cocos2d::Vector<SceneryLayer*> sceneryLayers;
    cocos2d::Vector<TerrainLayer*> terrainLayers;
    void setUpSceneryZOrders();
    cocos2d::LayerColor* background;

    std::unique_ptr<BiomeManager> biomeManager;
};

#endif // __HELLOWORLD_SCENE_H__
