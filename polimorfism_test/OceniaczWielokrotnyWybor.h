//
// Created by Magda on 14.04.2023.
//

#ifndef OCENIACZ_TESTOW_OCENIACZWIELOKROTNYWYBOR_H
#define OCENIACZ_TESTOW_OCENIACZWIELOKROTNYWYBOR_H
#include "Oceniacz.h"

class OceniaczWielokrotnyWybor : public Oceniacz{
public:
    int ocenPytanie(const Pytanie& p) const;
};


#endif //OCENIACZ_TESTOW_OCENIACZWIELOKROTNYWYBOR_H

