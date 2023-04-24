//
// Created by Magda on 12.04.2023.
//

#ifndef NAIWNY_POLIMORFIZM_WEAPON_H
#define NAIWNY_POLIMORFIZM_WEAPON_H
#include "Item.h"

class Weapon : public Item{
protected:
    int damage;
public:
    Weapon();
    Weapon(int _damage);
    int getDamage();
    void call(Character &c);
};


#endif //NAIWNY_POLIMORFIZM_WEAPON_H
