//
//  BiomeManager.hpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#ifndef BiomeManager_hpp
#define BiomeManager_hpp

#include "Biome.hpp"
#include <memory>

class BiomeManager {
public:
    BiomeManager();
    void step( float dt );
    const std::vector<std::string>& getScenerySpriteList() const;
    const Biome::FogInfo& getCurrentFogInfo() const;
private:
    std::unique_ptr<Biome> currentBiome, nextBiome;
    Biome::FogInfo currentFogInfo;
    float currentBiomeDuration, currentBiomeProgress;
    float tweenDuration, tweenProgress;
    enum class State {
        Normal,
        Tweening,
    } state;
    
    const Biome& getCurrentBiome() const;
    std::unique_ptr<Biome> getNextBiome();
    std::string lastPath;
};

#endif /* BiomeManager_hpp */
