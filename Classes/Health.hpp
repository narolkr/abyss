#ifndef Health_hpp
#define Health_hpp

#include "PickUp.hpp"

class Health:public PickUp{
public:    
    void effectsOnPlayer(Player* player) override;
    virtual bool init() override;
    CREATE_FUNC(Health);
private:
    float mHealthPointsPer;
};

#endif /* Health_hpp */
