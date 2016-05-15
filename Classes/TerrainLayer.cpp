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
    
    cocos2d::Size screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    this->setContentSize( screenSize );
    this->addChild( nodeContainer );
    
    addNewTerrainChunk();
    addNewTerrainChunk();
    
    ready = true;
    return true;
}

void TerrainLayer::step(float dt) {
    if ( !this->ready ) return;
    ScrollingLayer::step(dt);
}

void TerrainLayer::handleCycling( ScrollingLayer::MoveDirection moveDirection ) {
    TerrainChunk* front = this->terrainChunks.front();
    float absX = front->getPositionX() + nodeContainer->getPositionX();
    if ( absX <= -front->getContentSize().width ) {
        this->terrainChunks.pop_front();
        front->removeFromParent();
        
        this->addNewTerrainChunk();
    }
}

void TerrainLayer::addNewTerrainChunk() {
    cocos2d::Size size = this->getContentSize();
    TerrainChunk* newChunk = generator.nextTerrainChunk( size.width, size.height );
    nodeContainer->addChild( newChunk );
    
    if ( !this->terrainChunks.empty() ) {
        TerrainChunk* back = this->terrainChunks.back();
        float x = back->getPositionX() + back->getContentSize().width;
        newChunk->setPositionX( x );
    }
    this->terrainChunks.push_back( newChunk );
}

float TerrainLayer::getHeightForScreenXCoordinate(float x) {
    if ( x < 0 || x >= cocos2d::Director::getInstance()->getVisibleSize().width*2.f ) {
        throw std::invalid_argument( "invalid onscreen x coordinate" );
    }
    // get x in terms of our node container
    x = this->nodeContainer->convertToNodeSpace( cocos2d::Vec2( x, 0.f ) ).x;
    
    // find the chunk that x is over
    TerrainChunk* chunk;
    for ( auto& c : this->terrainChunks ) {
        if ( c->getPositionX() > x ) break;
        chunk = c;
    }
    // use that chunk to get the Y
    return chunk->getHeightForAbsoluteXCoordinate( x );
}
