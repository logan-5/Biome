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
    double stepX = width / (this->resolution-1);
    for ( int i = 0; i < this->points.size(); ++i ) {
        cocos2d::Vec2 point( i*stepX, this->points[i]*height );
        t->points.push_back( point );
    }
    t->setContentSize( cocos2d::Size( width, height ) );
    return t;
}

void TerrainGenerator::generatePoints() {
    this->points.clear();
    // TODO change this algorithm
    for ( int i = 0; i < resolution; ++i ) {
        this->points.push_back(startingHeight);
    }
    
    //std::srand(std::time(0));
    CCRANDOM_0_1();
    CCRANDOM_MINUS1_1();
    this->points[resolution-1] = CCRANDOM_0_1();
    midpointDisplace( points, 0, resolution, featureDecay );
    this->points[0] = startingHeight;
    startingHeight = this->points[resolution-1];
}

void TerrainGenerator::midpointDisplace( std::vector<double>& points, int min, int max, double decay ) {
    if ( max - min <= 1 ) {
        return;
    }
    
    double displacement = decay * roughness * cocos2d::rand_minus1_1();
    if ( max - min == 2 ) {
        points[min] += displacement;
        points[min+1] += displacement;
        return;
    }
    
    double midpoint = (points[max-1] + points[min]) / 2.0;
    int middleIndex = ((max-min) / 2.0) + min;
    points[middleIndex] = midpoint + displacement;
    
    midpointDisplace( points, min, middleIndex+1, decay*decay );
    midpointDisplace( points, middleIndex, max, decay*decay );
}
