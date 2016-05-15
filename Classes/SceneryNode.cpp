//
//  SceneryNode.cpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#include "SceneryNode.hpp"
#include "SceneryLayer.hpp"

using cocos2d::Vec2;

class SceneryNodeSprite : public cocos2d::Sprite {
public:
    static SceneryNodeSprite* create( const std::string& filename ) {
        SceneryNodeSprite *pRet = new(std::nothrow) SceneryNodeSprite();
        if (pRet && pRet->initWithFile( filename ) ) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    void onEnter() override;
};

void SceneryNodeSprite::onEnter() {
    cocos2d::Sprite::onEnter();
    this->setAnchorPoint( Vec2( 0.5f, 0.f ) );
    this->setNormalizedPosition( Vec2( 0.5, 0 ) );
    this->setFlippedX( cocos2d::rand_minus1_1() > 0 );
}

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

        auto biome = layer->getBiome();
        auto spriteList = biome.getScenerySprites();
        std::string filename = spriteList[spriteList.size()*cocos2d::rand_0_1()];
        this->sprite = SceneryNodeSprite::create( filename );

        this->addChild( sprite );
        this->sprite->setScale( layer->getSpriteScale() + layer->getSpriteScaleVar()*cocos2d::rand_minus1_1() );
    } else {
        if ( this->sprite ) this->sprite->setVisible( false );
    }
}
