#ifndef Walk_hpp
#define Walk_hpp

#include "Movement.hpp"

class Walk:public Movement{
public:
    void move(Character *character,float delta) override;
};

#endif /* Walk_hpp */
