//
//  TerrainLayer.cpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#include "TerrainLayer.hpp"

bool TerrainLayer::init() {
    if ( !cocos2d::Node::init() ) {
        return false;
    }
    nodeContainer = cocos2d::Node::create();
    this->addChild( nodeContainer );
    
    addNewTerrainChunk();
    addNewTerrainChunk();
    
    ready = true;
    return true;
}

void TerrainLayer::step(float dt) {
    if ( !this->ready ) return;
    float newX = nodeContainer->getPositionX() + dt * (1.f-this->distanceFactor);
    nodeContainer->setPositionX( newX );
    
    this->handleCycling();
}

void TerrainLayer::handleCycling() {
    TerrainChunk* front = this->terrainChunks.front();
    float absX = front->getPositionX() + nodeContainer->getPositionX();
    if ( absX <= -front->getContentSize().width ) {
        this->terrainChunks.pop_front();
        front->removeFromParent();
        
        this->addNewTerrainChunk();
    }
}

void TerrainLayer::addNewTerrainChunk() {
    cocos2d::Size screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    TerrainChunk* newChunk = generator.nextTerrainChunk( screenSize.width, screenSize.height );
    nodeContainer->addChild( newChunk );
    
    if ( !this->terrainChunks.empty() ) {
        TerrainChunk* back = this->terrainChunks.back();
        float x = back->getPositionX() + back->getContentSize().width;
        newChunk->setPositionX( x );
    }
    this->terrainChunks.push_back( newChunk );
}
