//
//  SceneryLayer.cpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#include "SceneryLayer.hpp"
#include "SceneryNode.hpp"
#include "MainScene.h"

using cocos2d::Vec2;
using cocos2d::Size;

bool SceneryLayer::init() {
    if ( !cocos2d::Node::init() ) {
        return false;
    }
    nodeContainer = cocos2d::Node::create();
    this->addChild( nodeContainer );
    hasSetNumberOfNodes = hasSetSizeX = false;
    setDensity( 1.f );
    initDistanceFactor( 0.f );
    setSpriteScale( 1.f );
    setSpriteScaleVar( .1f );
    return true;
}

void SceneryLayer::setUpSceneryNode() {
    float spacing = sizeX / (float)(numberOfNodes-1);
    for ( int i = 0; i < numberOfNodes; ++i ) {
        SceneryNode* sn = SceneryNode::create();
        nodeContainer->addChild( sn );
        this->sceneryNodes.push_back( sn );
        sn->setPosition( Vec2(i*spacing, 0.f) );
        sn->setContentSize( Size( spacing, 10.f ) );
        sn->layer = this;
    }
    this->ready = true;
}

void SceneryLayer::step(float absDist) {
    if ( !this->ready ) {
        return;
    }
    float dist = absDist * (1.f-this->distanceFactor);
    float newX = nodeContainer->getPositionX() + dist;
    nodeContainer->setPositionX( newX );
    
    auto fogInfo = this->getBiomeManager().getCurrentFogInfo();
    for ( auto& sn : this->sceneryNodes ) {
        sn->updateFog( fogInfo );
    }
    
    this->handleCycling( absDist > 0 ? MoveDirection::Backward : MoveDirection::Forward );
}

void SceneryLayer::handleCycling(MoveDirection direction) {
    bool shouldCycle = false;
    SceneryNode* cycleNode;
    switch ( direction ) {
        case MoveDirection::Forward: {
            cycleNode = this->sceneryNodes.front();
            if ( ( cycleNode->getPositionX() + nodeContainer->getPositionX() ) < -cycleNode->getContentSize().width ) {
                shouldCycle = true;
            }
            break;
        }
        case MoveDirection::Backward: {
            cycleNode = this->sceneryNodes.back();
            if ( ( cycleNode->getPositionX() + nodeContainer->getPositionX() ) > sizeX ) {
                shouldCycle = true;
            }
            break;
        }
    }
    if ( !shouldCycle ) return;
    
    float spacing = sizeX / (float)(numberOfNodes - 1);
    float deltaX;
    switch ( direction ) {
        case MoveDirection::Forward: {
            this->sceneryNodes.pop_front();
            this->sceneryNodes.push_back( cycleNode );
            deltaX = spacing*this->numberOfNodes;
            break;
        }
        case MoveDirection::Backward: {
            this->sceneryNodes.pop_back();
            this->sceneryNodes.push_front( cycleNode );
            deltaX = -spacing*this->numberOfNodes;
            break;
        }
    }
    float newX = cycleNode->getPositionX() + deltaX;
    cycleNode->setPositionX( newX );
    cycleNode->setUpSprite();
}

const BiomeManager& SceneryLayer::getBiomeManager() {
    return scene->getBiomeManager();
}
