//
//  TerrainGenerator.hpp
//  Biome
//
//  Created by Logan Smith on 5/15/16.
//
//

#ifndef TerrainGenerator_hpp
#define TerrainGenerator_hpp

#include "TerrainChunk.hpp"

class TerrainGenerator {
public:
    TerrainGenerator()
    : resolution(50.),
    roughness(.05),
    startingHeight(0.25),
    featureDecay(0.99)
    {}
    void setResolution( double resolution ) {
        this->resolution = resolution;
        this->points.reserve( resolution );
    }
    void setRoughness( double roughness ) {
        this->roughness = roughness;
    }
    
    TerrainChunk* nextTerrainChunk( float width, float height );
private:
    double resolution;
    double roughness;
    double featureDecay;
    double startingHeight;
    std::vector<double> points;
    
    void generatePoints();
    void midpointDisplace( std::vector<double>& points, int min, int max, double decay );
};

#endif /* TerrainGenerator_hpp */
