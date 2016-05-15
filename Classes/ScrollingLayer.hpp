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
     @param dist The amount to move.  Positive values move objects to the right (as though the camera were moving to the left), and the converse for negative values.
     */
    virtual void step( float dist );
    
    virtual void initDistanceFactor( float distanceFactor ) {
        if ( distanceFactor < 0 ) {
            std::invalid_argument( "invalid distance factor value, must be >= 0" );
            return;
        }
        distanceFactor = std::min<float>( distanceFactor, 1.f );
        this->distanceFactor = distanceFactor;
    }
    float getDistanceFactor() {
        return this->distanceFactor;
    }
protected:
    enum class MoveDirection {
        Forward,
        Backward,
    };
    
    virtual void handleCycling( MoveDirection direction )=0;
    cocos2d::Node* nodeContainer;
private:
    float distanceFactor;
};

#endif /* ScrollingLayer_hpp */
