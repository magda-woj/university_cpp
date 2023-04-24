//
// Created by Magda on 12.04.2023.
//

#include "Medicine.h"
#include "Item.h"
#include "Character.h"
#include <iostream>
Medicine::Medicine(){
    Item::type = "medicine";
    heal = 0;
}
Medicine::Medicine(int _heal){
    Item::type = "medicine";
    heal = _heal;
}
int Medicine::getHeal(){
    return heal;
}
void Medicine::call(Character &c){
    std::cout << "medicine has been used" << std::endl;
    c.setHP(std::min(c.getHP()+heal, 100));
}