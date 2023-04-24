//
// Created by Magda on 12.04.2023.
//

#include "Character.h"
#include "Item.h"
#include "Weapon.h"
#include "Medicine.h"
#include "MagicWeapon.h"
Character::Character(){
    hp = 100;
    defense = 0;
}
Character::Character(int _defense){
    hp = 100;
    defense = _defense;
}

Character::Character(int _defense, std::vector<Item*> &_items){
    hp = 100;
    defense = _defense;
    items = _items;
}
void Character::setHP(int _hp){
    hp = _hp;
}
int Character::getHP(){
    return hp;
}
void Character::setDefense(int _defense){
    defense = _defense;
}
int Character::getDefense(){
    return defense;
}
void Character::addItem(Item* i){
    items.push_back(i);
}
void Character::use(int i, Character &c){
    if(items[i]->getType() == "weapon")
    {
        Weapon* weaponPtr = dynamic_cast<Weapon*>(items[i]);
        weaponPtr->call(c);
        return;
    }
    if(items[i]->getType() == "medicine")
    {
        Medicine* medicinePtr = dynamic_cast<Medicine*>(items[i]);
        medicinePtr->call(c);
        return;
    }
    if(items[i]->getType() == "magic weapon")
    {
        MagicWeapon* weaponPtr = dynamic_cast<MagicWeapon*>(items[i]);
        weaponPtr->call(c);
        return;
    }
    items[i]->call(c);
}
