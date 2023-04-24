//
// Created by Magda on 19.04.2023.
//

#include "Person.h"

const std::string &Person::getName() const {
    return Name;
}

const std::string &Person::getSurname() const {
    return Surname;
}

Person::Person(const std::string &name, const std::string &surname) : Name(name), Surname(surname) {}

