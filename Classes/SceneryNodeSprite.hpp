//
//  SceneryNodeSprite.hpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#ifndef SceneryNodeSprite_hpp
#define SceneryNodeSprite_hpp

#include "cocos2d.h"
#include "Biome.hpp"

/** @class SceneryNodeSprite
 @brief A SceneryNodeSprite is simply a sprite with a custom fog shader.  It accepts fog info upon construction and can be updated with further fog info as the scene's fog changes.
 */
class SceneryNodeSprite : public cocos2d::Sprite {
public:
    static SceneryNodeSprite* create( const std::string& filename, float distanceFactor, const Biome::FogInfo& fogInfo ) {
        SceneryNodeSprite *pRet = new(std::nothrow) SceneryNodeSprite( distanceFactor, fogInfo );
        if (pRet && pRet->initWithFile( filename ) ) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    SceneryNodeSprite( float distanceFactor, const Biome::FogInfo& fogInfo )
    :   distanceFactor( distanceFactor ),
    fogInfo( &fogInfo )
    {}
    ~SceneryNodeSprite();
    
    void onExit() override;
    void onEnter() override;
    
    /**
     Update the fog info of the given sprite.  Its shader uniforms will be updated accordingly.
     */
    void setFogInfo( const Biome::FogInfo& fogInfo );
private:
    void setUpFogShader();
    float distanceFactor;
    const Biome::FogInfo* fogInfo;
    cocos2d::GLProgram* shaderProgram;
};

#endif /* SceneryNodeSprite_hpp */
