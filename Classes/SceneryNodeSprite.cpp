//
//  SceneryNodeSprite.cpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#include "SceneryNodeSprite.hpp"

using cocos2d::Vec2;
using cocos2d::GLProgram;

#define DISABLE_SHADER false

void SceneryNodeSprite::onEnter() {
    cocos2d::Sprite::onEnter();
    this->setAnchorPoint( Vec2( 0.5f, 0.f ) );
    this->setNormalizedPosition( Vec2( 0.5, 0 ) );
    this->setFlippedX( cocos2d::rand_minus1_1() > 0 );
    this->setUpFogShader();
}

// thank you @CitizenK at http://discuss.cocos2d-x.org/t/learning-and-using-opengl-shader/26551/8
// I miss Cocos2D-Spritebuilder 3.x
// where it's much simpler than this
void SceneryNodeSprite::setUpFogShader() {
#if !DISABLE_SHADER
    this->shaderProgram = GLProgram::createWithFilenames("ScenerySprite.vsh", "ScenerySprite.fsh");
    shaderProgram->link();
    shaderProgram->updateUniforms();
    shaderProgram->retain();
    shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    shaderProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    this->setGLProgram(shaderProgram);
    
    this->getGLProgramState()->setUniformTexture("u_texture", this->getTexture());
    this->getGLProgramState()->setUniformFloat("u_distanceFactor", this->distanceFactor);
    this->setFogInfo( *this->fogInfo );
#endif
}

inline cocos2d::Vec3 vec3FromColor4F( const cocos2d::Color4F& col ) {
    return cocos2d::Vec3( col.r, col.g, col.b );
}

void SceneryNodeSprite::setFogInfo( const Biome::FogInfo& fogInfo ) {
    this->fogInfo = &fogInfo;
#if !DISABLE_SHADER
    auto state = this->getGLProgramState();
    state->setUniformVec3( "u_fogColor", vec3FromColor4F(this->fogInfo->color) );
    state->setUniformFloat( "u_fogThickness", this->fogInfo->thickness );
#endif
}

void SceneryNodeSprite::onExit() {
    //this->setGLProgram(shaderProgram);
}

SceneryNodeSprite::~SceneryNodeSprite() {
    //this->setGLProgram(nullptr);
    this->shaderProgram->release();
    cocos2d::GLProgramCache::destroyInstance();
    //delete this->shaderProgram;
}
