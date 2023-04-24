//
// Created by Magda on 12.04.2023.
//
#pragma once
#ifndef NAIWNY_POLIMORFIZM_CHARACTER_H
#define NAIWNY_POLIMORFIZM_CHARACTER_H
#include "Item.h"
#include <vector>

class Character {
    int hp;
    int defense;
    std::vector<Item*> items;
public:
    Character();
    Character(int _defense);
    Character(int _defense, std::vector<Item*> &_items);
    void setHP(int _hp);
    int getHP();
    void setDefense(int _defense);
    int getDefense();
    void addItem(Item* i);
    void use(int i, Character &c);
};


#endif //NAIWNY_POLIMORFIZM_CHARACTER_H
