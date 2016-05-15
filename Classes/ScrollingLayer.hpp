//
//  ScrollingLayer.hpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#ifndef ScrollingLayer_hpp
#define ScrollingLayer_hpp

#include <exception>
#include "cocos2d.h"

/** @class ScrollingLayer
 @brief A `ScrollingLayer` is an abstract class that manages a group of objects that should be scrolled across the screen in a 'looping' fashion.  When an object goes past the boundary, it is 'cycled' back around to other side.  The `handleCycling` method is a pure virtual method and must be implemented by subclasses.
 
 The scrolling layer is moved by 'stepping' a given distance using the `step` method.  This can be called in an update loop for smooth scrolling.  Upon each step, the scrolling layer checks whether or not an overflow has occurred, and handles it.
 
 Technically, the scrolling layer does not have to take up the whole screen, since it scrolls and cycles within its own content size only.  This could be used to show objects moving past out a car window, for example.  This capability will probably never be used in this particular project.
 */
class ScrollingLayer {
public:
    ScrollingLayer()
    : nodeContainer( cocos2d::Node::create() )
    {}
    
    /**
     Move the scrolling layer the given distance.  Check for overflow and handle it.
     * @param dist The amount to move.  Positive values move objects to the right (as though the camera were moving to the left), and the converse for negative values.
     */
    virtual void step( float dist );
    
    /**
     * Set the 'distance factor' of the layer.  The distance factor affects the amount that the layer scrolls to simulate a parallax effect.  A distance factor of 0 is flush with the camera plane, 1 is infinitely far (no movement when scrolling).
     *
     * The distance factor can also be used for other purposes, e.g. determining the appropriate thickness of fog to apply to an object.
     *
     * The 'init' in the name should be self-documenting.  While it is possible to set the distance factor to a new value at any time, this will likely make the layer look like it "popped" into another plane.  I suppose you could smoothly animate the distance factor to achieve some sort of effect, but coolness not guaranteed.
     * @param distanceFactor The distance factor.  Should be between 0.0 and 1.0.
     */
    virtual void initDistanceFactor( float distanceFactor ) {
        if ( distanceFactor < 0 ) {
            std::invalid_argument( "invalid distance factor value, must be >= 0" );
            return;
        }
        distanceFactor = std::min<float>( distanceFactor, 1.f );
        this->distanceFactor = distanceFactor;
    }
    
    /**
     Get the distance factor for this layer.
     @see `initDistanceFactor`
     @return A float representing the distance of the layer to the camera.
     */
    float getDistanceFactor() {
        return this->distanceFactor;
    }
protected:
    enum class MoveDirection {
        Forward,
        Backward,
    };
    
    /**
     * Handle the cycling of nodes from one end of the screen back around to the other.  The `MoveDirection` is provided as either `MoveDirection::Forward` or `MoveDirection::Backward`.
     *
     * Must be implemented by subclasses.
     * @param direction Either `MoveDirection::Forward` or `MoveDirection::Backward`
     */
    virtual void handleCycling( MoveDirection direction )=0;
    
    /**
     The container for nodes that are scrolled.  Subclasses must add the `nodeContainer` to the scene in some meaningful way for the objects to appear, typically through `this->addChild( nodeContainer )`.
     */
    cocos2d::Node* nodeContainer;
private:
    float distanceFactor;
};

#endif /* ScrollingLayer_hpp */
