//
// Created by Magda on 12.04.2023.
//
#include <string>
#include <iostream>
#include "Item.h"
#include "Character.h"

void Item::call(Character &c){
    std::cout << "Item has been used" << std::endl;
}
Item::Item(){
    type = "";
}
Item::Item(std::string _type){
    type = _type;
}
std::string Item::getType(){
    return type;
}
