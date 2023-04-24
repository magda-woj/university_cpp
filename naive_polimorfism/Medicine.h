//
// Created by Magda on 12.04.2023.
//

#ifndef NAIWNY_POLIMORFIZM_MEDICINE_H
#define NAIWNY_POLIMORFIZM_MEDICINE_H
#include "Item.h"

class Medicine : public Item{
    int heal;
public:
    Medicine();
    Medicine(int _heal);
    int getHeal();
    void call(Character &c);
};


#endif //NAIWNY_POLIMORFIZM_MEDICINE_H
