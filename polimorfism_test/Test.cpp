//
// Created by Magda on 14.04.2023.
//
#include "Test.h"

const Person &Test::getExaminee() const {
    return examinee;
}

Pytanie Test::getQuestion(int i) const {
    return questions[i];
}

int Test::ocen(const Oceniacz& o){
    int n = 0;
    for(auto i: questions){
        n+=o.ocenPytanie(i);
    }
    return n;
}

Test::Test(const std::vector<Pytanie> &questions, const Person &examinee) : questions(questions), examinee(examinee) {}
