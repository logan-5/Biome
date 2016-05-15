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

    void onEnter() override;
    void setFogInfo( const Biome::FogInfo& fogInfo );
private:
    void setUpFogShader();
    float distanceFactor;
    const Biome::FogInfo* fogInfo;
};

#endif /* SceneryNodeSprite_hpp */
