//
//  Biome.cpp
//  Biome
//
//  Created by Logan Smith on 5/14/16.
//
//

#include "Biome.hpp"
#include <ostream>

Biome::Biome( FogInfo fogInfo, std::vector<std::string> scenerySprites )
:   scenerySprites( scenerySprites ),
fogInfo( fogInfo )
{}

Biome::Biome( std::string folderPath, FogInfo fogInfo )
:   fogInfo( fogInfo )
{
    std::ostringstream stringStream;
    stringStream << folderPath << "/tree.png";
    this->scenerySprites.push_back( stringStream.str() );
    
    stringStream.str(std::string());
    stringStream.clear();
    
    stringStream << folderPath << "/rock.png";
    this->scenerySprites.push_back( stringStream.str() );
}
