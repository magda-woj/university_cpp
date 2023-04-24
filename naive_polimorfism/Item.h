//
// Created by Magda on 12.04.2023.
//
#pragma once
#include <string>
#ifndef NAIWNY_POLIMORFIZM_ITEM_H
#define NAIWNY_POLIMORFIZM_ITEM_H

class Character;

class Item {
protected:
    std::string type;
public:
    virtual void call(Character &c);
    Item();
    Item(std::string _type);
    std::string getType();
};


#endif //NAIWNY_POLIMORFIZM_ITEM_H
