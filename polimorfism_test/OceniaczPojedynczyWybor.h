//
// Created by Magda on 14.04.2023.
//

#ifndef OCENIACZ_TESTOW_OCENIACZPOJEDYNCZYWYBOR_H
#define OCENIACZ_TESTOW_OCENIACZPOJEDYNCZYWYBOR_H
#include "Oceniacz.h"

class OceniaczPojedynczyWybor : public Oceniacz{
public:
    int ocenPytanie(const Pytanie& p) const;
};


#endif //OCENIACZ_TESTOW_OCENIACZPOJEDYNCZYWYBOR_H
