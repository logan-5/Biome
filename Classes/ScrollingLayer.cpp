//
//  ScrollingLayer.cpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#include "ScrollingLayer.hpp"

void ScrollingLayer::step( float absDist ) {
    if ( !nodeContainer->getParent() ) {
        cocos2d::log( "warning! node container has no parent" );
    }
    float dist = absDist * (1.f-this->distanceFactor);
    float newX = nodeContainer->getPositionX() + dist;
    nodeContainer->setPositionX( newX );

    this->handleCycling( absDist > 0 ? MoveDirection::Backward : MoveDirection::Forward );
}
