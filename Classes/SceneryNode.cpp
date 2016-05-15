//
//  SceneryNode.cpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#include "SceneryNode.hpp"
#include "SceneryLayer.hpp"
#include "SceneryNodeSprite.hpp"
#include "BiomeManager.hpp"

using cocos2d::Vec2;

bool SceneryNode::init() {
    if ( !cocos2d::Node::init() ) {
        return false;
    }
    return true;
}

void SceneryNode::onEnter() {
    cocos2d::Node::onEnter();
    this->setUpSprite();
}

void SceneryNode::setUpSprite() {
    if ( !layer ) {
        CCLOG( "scenery node must be added to a SceneryLayer before it is added to scene!" );
    }
    bool visibilityCoinToss = cocos2d::rand_0_1() < layer->getDensity();
    if ( visibilityCoinToss ) {
        if ( this->sprite ) this->sprite->removeFromParent();
        
        auto& biomeManager = layer->getBiomeManager();
        auto spriteList = biomeManager.getScenerySpriteList();
        std::string filename = spriteList[spriteList.size()*cocos2d::rand_0_1()];
        this->sprite = SceneryNodeSprite::create( filename, layer->getDistanceFactor(), biomeManager.getCurrentFogInfo() );
        
        this->addChild( sprite );
        this->sprite->setScale( layer->getSpriteScale() + layer->getSpriteScaleVar()*cocos2d::rand_minus1_1() );
    } else {
        if ( this->sprite ) this->sprite->setVisible( false );
    }
}

void SceneryNode::updateFog(const Biome::FogInfo &fogInfo) {
    if ( !this->sprite ) {
        return;
    }
    this->sprite->setFogInfo(fogInfo);
}
