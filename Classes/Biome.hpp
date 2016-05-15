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
    Biome( std::vector<std::string> scenerySprites, cocos2d::Color4B fogColor = cocos2d::Color4B::WHITE );

    const std::vector<std::string>& getScenerySprites() const {
        return scenerySprites;
    }
    const cocos2d::Color4B& getFogColor() const {
        return fogColor;
    }
private:
    std::vector<std::string> scenerySprites;
    cocos2d::Color4B fogColor;
};

#endif /* Biome_hpp */
