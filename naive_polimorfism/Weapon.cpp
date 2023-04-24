//
// Created by Magda on 12.04.2023.
//
#include "Item.h"
#include "Weapon.h"
#include "Character.h"
#include <iostream>
Weapon::Weapon(){
    Item::type = "weapon";
    damage = 0;
}
Weapon::Weapon(int _damage){
    Item::type = "weapon";
    damage = _damage;
}
int Weapon::getDamage(){
    return damage;
}
void Weapon::call(Character &c){
    std::cout << "weapon has been used" << std::endl;
    c.setHP(c.getHP()+c.getDefense()-damage);
}
