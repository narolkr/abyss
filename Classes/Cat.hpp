#ifndef Cat_hpp
#define Cat_hpp

#include "Enemy.h"

class Cat: public Enemy{
    
public:
    
    virtual bool init() override;
    CREATE_FUNC(Cat);
};

#endif /* Cat_hpp */
