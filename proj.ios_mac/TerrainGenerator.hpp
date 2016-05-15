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

/** @class TerrainGenerator
 @brief A TerrainGenerator instance randomly generates terrain using (as of now) some hacky bastardization of the Midpoint Displace algorithm.  It keeps track of its internal state so that the next terrain it generates is seamless with the previous one (with some considerations, see `nextTerrainChunk`).
 @todo Improve terrain generation algorithm.
 */
class TerrainGenerator {
public:
    TerrainGenerator()
    : resolution(50.),
    roughness(.05),
    startingHeight(0.25),
    featureDecay(0.99)
    {}
    
    /**
     Sets the "resolution" of the terrain generator (which is 50 by default).  The resolution is essentially the number of "divisions" within the terrain.
     @param resolution The new resolution.
     @todo Wait... why is resolution a double?  Shouldn't it be an int?
     */
    void setResolution( double resolution ) {
        this->resolution = resolution;
        this->points.reserve( resolution );
    }
    
    /**
     Sets the "roughness" of the terrain generator (which is 0.05 by default).  The roughness represents the amount of displacement that can be applied between terrain steps.
     */
    void setRoughness( double roughness ) {
        this->roughness = roughness;
    }
    
    /**
     Get a TerrainChunk instance based on the next batch of terrain.  The terrain is guaranteed to be seamless with the last-generated terrain IF AND ONLY IF `width` and `height` are the same as last time.  In most cases, this method will be invoked by a TerrainLayer class which uses its content size as the parameters, so changing the content size of a TerrainLayer at an arbitrary time might make your terrain not link up properly.
     @param width The width of the newly-generated TerrainChunk.
     @param height The height of the newly-generated TerrainChunk.
     */
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
