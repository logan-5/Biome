//
//  TerrainChunk.cpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#include "TerrainChunk.hpp"
#include "CCDrawingPrimitives.h"

/*void TerrainChunk::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) {
 // cocos2d::log("drawing line");
 for ( int i = 0; i < points.size()-1; ++i ) {
 cocos2d::DrawPrimitives::drawLine( points[i], points[i+1] );
 }
 }*/

bool TerrainChunk::init() {
    if(!cocos2d::Layer::init()) {
        return false;
    }
    _DEBUGGING_ONLY_lineColor = cocos2d::Color4F( CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1.f );
    return true;
}

void TerrainChunk::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags){
    cocos2d::Layer::draw(renderer, transform, flags);
    
    _customCmd.init(_globalZOrder);
    _customCmd.func = CC_CALLBACK_0(TerrainChunk::onDraw, this, transform, flags);
    renderer->addCommand(&_customCmd);
}

void TerrainChunk::onDraw(const cocos2d::Mat4 &transform, uint32_t flags) {
    cocos2d::Director* director = cocos2d::Director::getInstance();
    director->pushMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    // deprecated
    /*kmGLPushMatrix();
     kmGLLoadMatrix(&transform);*/
    
    cocos2d::DrawPrimitives::setDrawColor4F(_DEBUGGING_ONLY_lineColor.r, _DEBUGGING_ONLY_lineColor.g, _DEBUGGING_ONLY_lineColor.b, _DEBUGGING_ONLY_lineColor.a );
    for ( int i = 0; i < points.size()-1; ++i ) {
        cocos2d::DrawPrimitives::drawLine( points[i], points[i+1] );
    }
}

float TerrainChunk::getHeightForAbsoluteXCoordinate(float x) {
    x -= this->getPositionX();
    unsigned long pointCount = points.size();
    float fraction = (float)pointCount * (x / this->getContentSize().width);
    unsigned long index = (unsigned long)fraction;
    float minValue = points[index].y;
    float maxValue = points[index+1].y;
    float factor = fraction - index;
    
    return minValue + factor*(maxValue-minValue);
}
