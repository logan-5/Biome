//
//  Biome.hpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#ifndef Biome_hpp
#define Biome_hpp

#include <vector>

struct Biome {
public:
    friend class MainScene;
    struct FogInfo {
        const cocos2d::Color4F color;
        const float thickness;
        FogInfo( cocos2d::Color4F color = cocos2d::Color4F::WHITE, float thickness = 1.f )
        :   color( color ),
        thickness( thickness )
        {}
    };

    Biome( FogInfo fogInfo = FogInfo(), std::vector<std::string> scenerySprites = std::vector<std::string>() );

    const std::vector<std::string>& getScenerySprites() const {
        return scenerySprites;
    }
    const cocos2d::Color4F& getFogColor() const {
        return fogInfo.color;
    }
    const float getFogThickness() const {
        return fogInfo.thickness;
    }
    const FogInfo& getFogInfo() const {
        return this->fogInfo;
    }

private:
    std::vector<std::string> scenerySprites;
    FogInfo fogInfo;
};

#endif /* Biome_hpp */
