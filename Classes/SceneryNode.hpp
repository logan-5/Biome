//
//  SceneryNode.hpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#ifndef SceneryNode_hpp
#define SceneryNode_hpp

#include "cocos2d.h"
#include "Biome.hpp"

class SceneryNodeSprite;
class SceneryLayer;

/** @class SceneryNode
 @brief A SceneryNode manages a SceneryNodeSprite, updating it based on the parent SceneryLayer's density as well as the current biome's available sprite list.
 */
class SceneryNode : public cocos2d::Node {
public:
    friend class SceneryLayer;
    CREATE_FUNC(SceneryNode);
    bool init() override;
    void onEnter() override;
    
    /**
     Selects a new sprite based on the current biome's available sprite list, and/or sets the sprite to invisible based on the SceneryLayer's density.
     */
    void setUpSprite();
    
    /**
     Passes fog info along to the child sprite's shader.
     */
    void updateFog( const Biome::FogInfo& fogInfo );
private:
    SceneryLayer* layer;
    SceneryNodeSprite* sprite;
};

#endif /* SceneryNode_hpp */
