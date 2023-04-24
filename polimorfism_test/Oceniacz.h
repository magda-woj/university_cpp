//
// Created by Magda on 14.04.2023.
//

#ifndef OCENIACZ_TESTOW_OCENIACZ_H
#define OCENIACZ_TESTOW_OCENIACZ_H
#include <vector>
#include "Pytanie.h"

class Oceniacz {
public:
    virtual int ocenPytanie(const Pytanie &p) const;
};


#endif //OCENIACZ_TESTOW_OCENIACZ_H
