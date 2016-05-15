//
//  SceneryLayer.hpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#ifndef SceneryLayer_hpp
#define SceneryLayer_hpp

#include "cocos2d.h"
#include <deque>
#include "TerrainLayer.hpp"
#include "ScrollingLayer.hpp"
class BiomeManager;

class SceneryNode;
class MainScene;

/** @class SceneryLayer
 @brief A SceneryLayer houses a number of objects (given by `numberOfNodes`) that scroll across the screen in a looping fashion.  The nodes will either be sprites corresponding to the current biome, or empty (based on `density`).  The looping is accomplished using the `ScrollingLayer` interface.
 
 For a SceneryLayer to work, you MUST call `initSizeX` as well as `initNumberOfNodes`.  This allows the layer to create its nodes and calculate their spacing.  It will not do anything unless both of these methods are called.
 
 A SceneryLayer can own a pointer to a TerrainLayer object, which the SceneryLayer will use to determine the heights of its nodes.  If it has no TerrainLayer object, it will simply set all its nodes' heights to 0.  For best results, the `distanceFactor` of a SceneryLayer and its TerrainLayer should be identical.  To this end, calling `initDistanceFactor` on a SceneryLayer will also call that of its TerrainLayer, if any.
 */
class SceneryLayer : public cocos2d::Node, public ScrollingLayer {
public:
    CREATE_FUNC(SceneryLayer);
    
    bool init() override;
    
    /**
     * Set the x size of the SceneryLayer.  This will determine how wide it spans (from 0...x).  When objects move past the boundaries, they will cycle back around to the other side.
     * 
     * Can only be set once.
     @param sizeX The x size of the SceneryLayer.
     */
    void initSizeX( float sizeX ) {
        if ( hasSetSizeX ) {
            CCLOG( "sizeX already set for scenery node!" );
            return;
        }
        this->sizeX = sizeX;
        hasSetSizeX = true;
        if ( hasSetNumberOfNodes ) {
            this->setUpSceneryNode();
        }
    }
    
    /**
     * Set the number of nodes in the SceneryLayer.  This will affect the spacing of the nodes, as well as, of course, the number.  The spacing of the nodes is a function of the number of nodes and the size; 10 nodes with a given size X will be more tightly packed than 5 nodes with the same X.
     * 
     * Can only be set once.
     @param numberOfNodes The number of nodes in the SceneryLayer.
     */
    void initNumberOfNodes( int numberOfNodes ) {
        if ( hasSetNumberOfNodes ) {
            CCLOG( "numberOfNodes already set for scenery node!" );
            return;
        }
        this->numberOfNodes = numberOfNodes+1;
        hasSetNumberOfNodes = true;
        if ( hasSetSizeX ) {
            this->setUpSceneryNode();
        }
    }
    
    void initDistanceFactor( float distanceFactor) override {
        SceneryLayer::ScrollingLayer::initDistanceFactor( distanceFactor );
        if ( this->terrain ) this->terrain->initDistanceFactor( distanceFactor );
    }
    
    /**
     * The base density of a scenery layer is a decimal from 0.0 to 1.0 representing the likelihood of each "slot" in the scenery layer being filled with a visible sprite.  At 0.0, no sprites will appear.  At 1.0, every slot will be filled with a sprite 100% of the time.
     * 
     * The density can also be changed at arbitrary times.  This could be used for a cool effect, e.g. animating the density from 0.8 to 0.3 to create an effect of a thick forest gradually thinning out.
     @param density The new density of the layer.
     */
    void setDensity( float density ) {
        this->density = cocos2d::clampf( density, 0.f, 1.f );
    }
    /**
     * Get the base density of the layer.
     @see `setDensity`
     */
    float getDensity() {
        return this->density;
    }

    /**
     * Sets the scale of all sprites in this layer.  Most intuitively used to scale down an entire layer to create a distance effect.
     @param spriteScale Set the new sprite scale;
     */
    void setSpriteScale( float spriteScale ) {
        this->spriteScale = spriteScale;
    }
    /**
     * Gets the sprite scale.
     @see `setSpriteScale`
     */
    float getSpriteScale() {
        return this->spriteScale;
    }
    /**
     * Sprite scale variance.  A given sprite in this layer will have scale equal to this->spriteScale +/- this->spriteScaleVar.  Use this to randomize (or de-randomize) the scale of objects in the layer.  Default is 0.1.
     @param spriteScaleVar The new sprite scale variance.
     */
    void setSpriteScaleVar( float spriteScaleVar ) {
        this->spriteScaleVar = spriteScaleVar;
    }
    /**
     * Get the sprite scale variance.
     @see `setSpriteScaleVar`
     */
    float getSpriteScaleVar() {
        return this->spriteScaleVar;
    }
    /**
     * Sets a pointer to the current scene.  Important so the scenery layer can query the scene's BiomeManager.
     */
    void setScene( MainScene* scene ) {
        this->scene = scene;
    }
    /**
     * Links the given terrain layer to this SceneryLayer.  This layer's objects will now appear at the height given by the terrain (though not retroactively--future objects only), and their distances from the camera will be synced.
     @param t TerrainLayer to link, or `nullptr` to clear the linkage.
     */
    void initTerrainLayer( TerrainLayer* t ) {
        this->terrain = t;
        if ( this->terrain ) {
            t->initDistanceFactor( this->getDistanceFactor() );
            t->setLocalZOrder( this->getLocalZOrder() );
        }
    }

    /**
     * Gets the current scene's BiomeManager.  Called by child nodes.
     */
    const BiomeManager& getBiomeManager();
    
    void step( float absDist ) override;
    
private:
    std::deque<SceneryNode*> sceneryNodes;
    
    MainScene* scene;
    int numberOfNodes;
    float sizeX;
    
    float density;
    float spriteScale, spriteScaleVar;
    bool hasSetNumberOfNodes, hasSetSizeX, ready;
    TerrainLayer* terrain;
    
    void setUpSceneryNode();
    void handleCycling( MoveDirection direction ) override;
    float getYPositionForNode( const SceneryNode& node, float xOffset = 0 );
};

#endif /* SceneryLayer_hpp */
