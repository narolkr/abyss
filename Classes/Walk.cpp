#include "Walk.hpp"

void Walk::move(Character *character,float delta){
    character->getSprite()->setFlipX(mDir);
    if(mDir == EDIR::left){
        character->setPositionX(character->getPositionX()+(delta*mSpeed*-1));
    }else{
        character->setPositionX(character->getPositionX()+(delta*mSpeed*1));
    }
}
