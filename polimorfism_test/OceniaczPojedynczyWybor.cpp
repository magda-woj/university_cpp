//
// Created by Magda on 14.04.2023.
//

#include "OceniaczPojedynczyWybor.h"

int OceniaczPojedynczyWybor::ocenPytanie(const Pytanie& p) const{
    if(p.nOfBad()!=0) return 0;
    if(p.nOfUnmarked() != p.nOfAns()-1) return 0;
    return 1;
}
