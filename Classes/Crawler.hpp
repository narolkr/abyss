//
//  Crawler.hpp
//  abyss
//
//  Created by Longkumer, Narosenla on 11/06/18.
//

#ifndef Crawler_hpp
#define Crawler_hpp

#include "Enemy.h"

class Crawler: public Enemy{
    
public:
    
    virtual bool init() override;
    CREATE_FUNC(Crawler);
};

#endif /* Crawler_hpp */
