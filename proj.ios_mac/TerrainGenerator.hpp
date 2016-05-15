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
    : features(5),
    featureSize(.25),
    startingHeight(0.25),
    smoothing(25)
    {}
    
    /**
     Sets the number of features in the next terrain chunk.  A feature is essentially a "division" within the terrain.
     @param features The new number of features.
     */
    void setFeatures( int features ) {
        this->features = features;
    }
    
    /**
     Sets the "featureSize" of the terrain generator (which is 0.05 by default).  The featureSize represents the amount of displacement that can be applied between terrain steps.
     */
    void setfeatureSize( double featureSize ) {
        this->featureSize = featureSize;
    }
    
    /**
     Sets the smoothness of the terrain, which adds steps in between resolution steps to interpolate on a curve.
     */
    void setSmoothing( int smoothing ) {
        this->smoothing = smoothing;
    }
    
    /**
     Get a TerrainChunk instance based on the next batch of terrain.  The terrain is guaranteed to be seamless with the last-generated terrain IF AND ONLY IF `width` and `height` are the same as last time.  In most cases, this method will be invoked by a TerrainLayer class which uses its content size as the parameters, so changing the content size of a TerrainLayer at an arbitrary time might make your terrain not link up properly.
     @param width The width of the newly-generated TerrainChunk.
     @param height The height of the newly-generated TerrainChunk.
     */
    TerrainChunk* nextTerrainChunk( float width, float height );
private:
    int features;
    double featureSize;
    double startingHeight;
    int smoothing;
    std::vector<double> points;
    
    void generatePoints();
    void midpointDisplace( std::vector<double>& points, int min, int max );
};

#endif /* TerrainGenerator_hpp */
