#include "Enemy.h"

#ifndef Spike_h
#define Spike_h

class Spike:public Enemy{
    
public:
    
    virtual bool init() override;
    CREATE_FUNC(Spike);
    
};
#endif /* Spike_h */
