//
// Created by Magda on 14.04.2023.
//

#ifndef OCENIACZ_TESTOW_TEST_H
#define OCENIACZ_TESTOW_TEST_H
#include <vector>

#include "Person.h"
#include "Pytanie.h"
#include "Oceniacz.h"

class Test {
    std::vector<Pytanie> questions;
    Person examinee;
public:
    Test(const std::vector<Pytanie> &questions, const Person &examinee);

    const Person &getExaminee() const;

    Pytanie getQuestion(int i) const;

    int ocen(const Oceniacz& o);
};


#endif //OCENIACZ_TESTOW_TEST_H
