//
// Created by Magda on 12.04.2023.
//

#ifndef NAIWNY_POLIMORFIZM_MAGICWEAPON_H
#define NAIWNY_POLIMORFIZM_MAGICWEAPON_H
#include "Weapon.h"

class MagicWeapon : public Weapon{
    void (*magicEffect)(Character &c);
public:
    MagicWeapon(int _damage, void (*_magicEffect)(Character &c) );
    void call(Character &c);
};


#endif //NAIWNY_POLIMORFIZM_MAGICWEAPON_H
