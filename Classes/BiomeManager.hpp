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
#include "TerrainGenerator.hpp"
#include <memory>

/** @class BiomeManager
 @brief A BiomeManager instance handles the current biome, as well as gradual transitioning from one biome to the next.  On the edge of one biome, the BiomeManager will select a new biome and begin "tweening" the current biome to the new one.
 
 By default, a BiomeManager sets the "duration" of the current biome to a random number between 20.0 and 30.0, and the duration of tweens (see below) to a random number between 5.0 and 10.0.
 
 Given a scene with a BiomeManager, the objects in the scene can query the BiomeManager for the current fog color and current available list of sprites.  Based on the current biome state, this might be a 'blend' of the old biome and the oncoming next biome.  Thus it is very different from querying the current biome directly, which does not allow the BiomeManager to interpolate.  Thus, directly accessing properties of a Biome object is discouraged.
 
 You can 'move through' the current biome by calling `BiomeManager::step`.  At the moment, only "forward" (conceptually, "camera to the right, biome to the left") stepping is supported.
 
 BiomeManager stepping is completely unrelated to ScrollingLayer stepping, so you can step your scrolling layers without ever stepping your BiomeManager (thereby staying in the same biome forever), or stop stepping halfway through a BiomeManager tween (thereby staying in a strange half-forest half-desert forever).
 */
class BiomeManager {
public:
    BiomeManager();
    /**
     "Move through" the current biome by `dt`.  When the current biome is moved all the way through, tweening to the next biome will begin.
     @param dt The amount to move through the current biome.
     */
    void step( float dt );
    /**
     The list of available sprites at this current moment in biome-land.  Usually corresponds to the sprites in a given biome, but when blending between two biomes, it might be different.
     @return The list of available sprites.
     */
    const std::vector<std::string>& getScenerySpriteList() const;
    /**
     Get the current fog info.  In normal circumstances, will correspond to the fog of the current biome.  When blending between two biomes, will be a linear interpretation of their two fog settings.
     @return The fog info for this moment in biome-land.
     */
    const Biome::FogInfo& getCurrentFogInfo() const;
    //TerrainGenerator& getTerrainGenerator() const;
private:
    std::string lastPath;
    std::unique_ptr<Biome> currentBiome, nextBiome;
    //std::unique_ptr<TerrainGenerator> terrainGenerator;
    Biome::FogInfo currentFogInfo;
    float currentBiomeDuration, currentBiomeProgress;
    float tweenDuration, tweenProgress;
    enum class State {
        Normal,
        Tweening,
    } state;
    
    const Biome& getCurrentBiome() const;
    std::unique_ptr<Biome> getNextBiome();
};

#endif /* BiomeManager_hpp */
