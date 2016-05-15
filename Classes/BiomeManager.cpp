//
//  BiomeManager.cpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#include "BiomeManager.hpp"

cocos2d::Color4F tweenColors( cocos2d::Color4F c1, cocos2d::Color4F c2, float fac ) {
    fac = cocos2d::clampf( fac, 0.f, 1.f );
    float r = c1.r + fac*(c2.r - c1.r);
    float g = c1.g + fac*(c2.g - c1.g);
    float b = c1.b + fac*(c2.b - c1.b);
    float a = c1.a + fac*(c2.a - c1.a);
    return cocos2d::Color4F( r, g, b, a );
}

Biome::FogInfo tweenFogInfo( Biome::FogInfo f1, Biome::FogInfo f2, float fac ) {
    fac = cocos2d::clampf( fac, 0.f, 1.f );
    float thickness = f1.thickness + fac*(f2.thickness - f1.thickness);
    cocos2d::Color4F color = tweenColors( f1.color, f2.color, fac );
    return Biome::FogInfo( color, thickness );
}

BiomeManager::BiomeManager()
: nextBiome( std::unique_ptr<Biome>( nullptr ) ),
currentBiomeDuration( 0.f ),
currentBiomeProgress( 0.f ),
tweenDuration( 0.f ),
tweenProgress( 0.f ),
lastPath("Biome1"),
state(State::Normal)
{
    currentBiome = std::unique_ptr<Biome>( new Biome(lastPath) );
    currentBiomeDuration = cocos2d::random( 10.f, 20.f );
}

void BiomeManager::step(float dt) {
    switch ( this->state ) {
        case State::Normal: {
            currentBiomeProgress += dt;
            if ( currentBiomeProgress >= currentBiomeDuration ) {
                CCLOG("started tweening");
                this->state = State::Tweening;
                tweenProgress = currentBiomeProgress - currentBiomeDuration;
                currentBiomeProgress = currentBiomeDuration = 0.f;
                
                nextBiome = this->getNextBiome();
                tweenDuration = cocos2d::random( 5.f, 10.f );
                
                currentFogInfo = tweenFogInfo( currentBiome->fogInfo, nextBiome->fogInfo, tweenProgress/tweenDuration );
            }
            break;
        }
        case State::Tweening: {
            tweenProgress += dt;
            if ( tweenProgress >= tweenDuration ) {
                CCLOG("finished tweening");
                this->state = State::Normal;
                currentBiomeProgress = tweenProgress - tweenDuration;
                tweenProgress = tweenDuration = 0.f;
                
                // a little fuzzy on the semantics of unique_ptr.  I'm usually a shared_ptr kinda guy
                currentBiome = std::move(nextBiome); // I believe this is necessary to guarantee the uniqueness of the pointer.  unique_ptr cannot be copied
                nextBiome = std::unique_ptr<Biome>( nullptr ); // necessary?
                currentBiomeDuration = cocos2d::random( 10.f, 20.f );
                
                currentFogInfo = currentBiome->fogInfo;
            } else {
                currentFogInfo = tweenFogInfo( currentBiome->fogInfo, nextBiome->fogInfo, tweenProgress/tweenDuration );
            }
            break;
        }
    }
}

std::unique_ptr<Biome> BiomeManager::getNextBiome() {
    std::string path = (lastPath == "Biome1") ? "Biome2" : "Biome1";
    lastPath = path;
    
    cocos2d::Color4F nextFogColor( cocos2d::rand_0_1(), cocos2d::rand_0_1(), cocos2d::rand_0_1(), cocos2d::rand_0_1() );
    Biome::FogInfo nextFogInfo( nextFogColor, 2.f*cocos2d::rand_0_1() );
    Biome* nextBiome = new Biome( path, nextFogInfo );
    return std::unique_ptr<Biome>( nextBiome );
}

const Biome& BiomeManager::getCurrentBiome() const {
    switch (this->state) {
        case State::Tweening: {
            bool coinToss = cocos2d::rand_0_1() < (tweenProgress / tweenDuration);
            return coinToss ? *nextBiome : *currentBiome;
            break;
        }
        case State::Normal:
        default: {
            return *currentBiome;
            break;
        }
    }
}

const std::vector<std::string>& BiomeManager::getScenerySpriteList() const {
    return getCurrentBiome().scenerySprites;
}

const Biome::FogInfo& BiomeManager::getCurrentFogInfo() const {
    return currentFogInfo;
}
