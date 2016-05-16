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
    textureSprite = cocos2d::Sprite::create( "ground.png" );
    textureSprite->retain();
    
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
    
    
    cocos2d::DrawPrimitives::setDrawColor4F(_DEBUGGING_ONLY_lineColor.r, _DEBUGGING_ONLY_lineColor.g, _DEBUGGING_ONLY_lineColor.b, _DEBUGGING_ONLY_lineColor.a );
    for ( int i = 0; i < points.size()-1; ++i ) {
        cocos2d::DrawPrimitives::drawLine( points[i], points[i+1] );
    }
    
    using namespace cocos2d;
    auto texture = textureSprite->getTexture();
    
    //    CC_NODE_DRAW_SETUP();
    texture->getGLProgram()->use();
    texture->getGLProgram()->setUniformsForBuiltins();
    GL::bindTexture2D(texture->getName());
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD );
    
    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, texCoords.data());
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)vertices.size());
}

void TerrainChunk::setPoints( const std::vector<cocos2d::Vec2>& points ) {
    this->points = points;
    vertices.clear();
    texCoords.clear();
    
    cocos2d::Vec2 point1 = points[0], point2 = points[1];
    
    vertices.push_back( terrain_vertex(point1.x, 0.) );
    vertices.push_back( terrain_vertex(point2.x, 0.) );
    vertices.push_back( terrain_vertex(point1.x, point1.y) );
    vertices.push_back( terrain_vertex(point2.x, point2.y) );
    
    texCoords.push_back( terrain_vertex( fmodf(point1.x,512)/512, 1. ) );
    texCoords.push_back( terrain_vertex( fmodf(point1.x,512)/512, 0. ) );
    texCoords.push_back( terrain_vertex( fmodf(point2.x,512)/512, 1. ) );
    texCoords.push_back( terrain_vertex( fmodf(point2.x,512)/512, 0. ) );
    
    // TODO: make this better
    for ( int i = 0; i < points.size(); ++i ) {
        cocos2d::Vec2 point1 = points[i], point2 = points[i+1];
        
        vertices.push_back( terrain_vertex(point1.x, 0.) );
        //vertices.push_back( terrain_vertex(point2.x, 0.) );
        vertices.push_back( terrain_vertex(point1.x, point1.y) );
        //vertices.push_back( terrain_vertex(point2.x, point2.y) );
        
        texCoords.push_back( terrain_vertex( 0., fmodf(point1.x,512)/512 ) );
        texCoords.push_back( terrain_vertex( 1., fmodf(point1.x,512)/512 ) );
        //texCoords.push_back( terrain_vertex( fmodf(point2.x,512)/512, 1. ) );
        //texCoords.push_back( terrain_vertex( fmodf(point2.x,512)/512, 0. ) );
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

void TerrainChunk::onExit() {
    Layer::onExit();
    if ( this->textureSprite ) {
        textureSprite->release();
    }
}
