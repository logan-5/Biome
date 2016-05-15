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

class SceneryNodeSprite;
class SceneryLayer;

class SceneryNode : public cocos2d::Node {
public:
    friend class SceneryLayer;
    CREATE_FUNC(SceneryNode);
    bool init() override;
    void onEnter() override;
    void setUpSprite();
private:
    SceneryLayer* layer;
    SceneryNodeSprite* sprite;
};

#endif /* SceneryNode_hpp */
