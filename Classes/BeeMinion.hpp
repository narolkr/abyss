#ifndef BeeMinion_hpp
#define BeeMinion_hpp

#include "Enemy.h"

class BeeMinion:public Enemy{
    
public:
    
    virtual bool init() override;
    CREATE_FUNC(BeeMinion);
};

#endif /* BeeMinion_hpp */
