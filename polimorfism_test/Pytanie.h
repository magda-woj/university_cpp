//
// Created by Magda on 14.04.2023.
//

#ifndef OCENIACZ_TESTOW_PYTANIE_H
#define OCENIACZ_TESTOW_PYTANIE_H

#include <vector>
class Pytanie {
    enum Odpowiedzi{
        BAD_MARKED,
        BAD_UNMARKED,
        OK_MARKED,
        OK_UNMARKED
    };
    std::vector<Odpowiedzi> ans;
public:
    Pytanie(int n);
    explicit Pytanie(const std::vector<Odpowiedzi> &ans);

    int nOfAns() const;
    int getBad_Marked() const;
    int getOK_Marked() const;
    int getBad_Unmarked() const;
    int getOK_Unmarked() const;
    int nOfBad() const;
    int nOfOk() const;
    int nOfUnmarked() const;
};


#endif //OCENIACZ_TESTOW_PYTANIE_H
