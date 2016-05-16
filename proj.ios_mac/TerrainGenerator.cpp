//
//  TerrainGenerator.cpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#include "TerrainGenerator.hpp"

TerrainChunk* TerrainGenerator::nextTerrainChunk(float width, float height) {
    this->generatePoints();
    
    TerrainChunk* t = TerrainChunk::create();
    double stepX = width / (this->points.size()-1);
    std::vector<cocos2d::Vec2> p;
    for ( int i = 0; i < this->points.size(); ++i ) {
        cocos2d::Vec2 point( i*stepX, this->points[i]*height );
        p.push_back( point );
    }
    t->setPoints( std::move( p ) );
    t->setContentSize( cocos2d::Size( width, height ) );
    return t;
}

void TerrainGenerator::generatePoints() {
    this->points.clear();
    
    // TODO change this algorithm
    decltype(this->points) newPoints;
    newPoints.reserve( features );
    for ( int i = 0; i < features; ++i ) {
        newPoints.push_back(startingHeight);
    }
    
    //std::srand(std::time(0));
    CCRANDOM_0_1();
    CCRANDOM_MINUS1_1();
    newPoints[features-1] = CCRANDOM_0_1();
    midpointDisplace( newPoints, 0, features );
    newPoints[0] = startingHeight;
    
    // add smoothing
    if ( this->smoothing > 0 ) {
        decltype(newPoints) tempNewPoints;
        tempNewPoints.reserve( features*(1+this->smoothing) );
        
        double deltaAngle = M_PI / (this->smoothing+1.0);
        int i = 0;
        for ( ; i < newPoints.size()-1; ++i ) {
            tempNewPoints.push_back( newPoints[i] );
            double ampl = (newPoints[i] - newPoints[i+1]) / 2.0;
            double midpoint = (newPoints[i] + newPoints[i+1]) / 2.0;
            for ( int j = 1; j <= this->smoothing; ++j ) {
                double ang = deltaAngle*j;
                double y = cos(ang) * ampl + midpoint;
                tempNewPoints.push_back(y);
            }
        }
        tempNewPoints.push_back(newPoints[i]);
        
        newPoints = std::move(tempNewPoints);
    }
    this->points = newPoints;
    this->startingHeight = newPoints.back();
}

void TerrainGenerator::midpointDisplace( std::vector<double>& points, int min, int max ) {
    if ( max - min <= 1 ) {
        return;
    }
    
    double displacement = featureSize * cocos2d::rand_minus1_1();
    if ( max - min == 2 ) {
        points[min] += displacement;
        points[min+1] += displacement;
        return;
    }
    
    double midpoint = (points[max-1] + points[min]) / 2.0;
    int middleIndex = ((max-min) / 2.0) + min;
    points[middleIndex] = midpoint + displacement;
    
    midpointDisplace( points, min, middleIndex+1 );
    midpointDisplace( points, middleIndex, max );
}
