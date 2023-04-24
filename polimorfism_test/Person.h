//
// Created by Magda on 19.04.2023.
//

#ifndef OCENIACZ_TESTOW_PERSON_H
#define OCENIACZ_TESTOW_PERSON_H
#include <string>

class Person {
    std::string Name;
    std::string Surname;
public:

    Person(const std::string &name, const std::string &surname);

    const std::string &getName() const;
    const std::string &getSurname() const;
};


#endif //OCENIACZ_TESTOW_PERSON_H
