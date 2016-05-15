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
    const std::vector<std::string>& getScenerySprites() const {
        return scenerySprites;
    }
private:
    std::vector<std::string> scenerySprites;
};

#endif /* Biome_hpp */
