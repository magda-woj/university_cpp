//
// Created by Magda on 12.04.2023.
//

#include "MagicWeapon.h"
MagicWeapon::MagicWeapon(int _damage, void (*_magicEffect)(Character &c) ){
    Weapon::damage = _damage;
    Item::type = "magic weapon";
    magicEffect = _magicEffect;
}
void MagicWeapon::call(Character &c){
    magicEffect(c);
    Weapon::call(c);
}