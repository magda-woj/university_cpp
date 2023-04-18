// Magda Wójtowicz
// Created by Magda on 07.04.2023.
//
#include "Z3.h"
#include <string>
#include <iostream>
#ifndef BACACLION_POLYNOMIAL_H
#define BACACLION_POLYNOMIAL_H


class Polynomial {
    unsigned int deg;
    Z3 *coeffs;
public:
    Polynomial();
    Polynomial(unsigned int _deg, Z3 _coeffs[]);
    Polynomial(const Polynomial& O);
    ~Polynomial();
    Z3& operator[](int i);
    Z3& operator[](int i) const;
    void resize();
    Polynomial operator +=(const Polynomial& Q);
    Polynomial operator -=(const Polynomial& Q);
    Polynomial operator *=(const Polynomial& Q);
    Polynomial operator *=(const Z3& s);
    Polynomial operator *=(Z3& s);
    Polynomial operator /=(const Z3& s);
    void operator=(const Polynomial& oP);
    unsigned int degree() const;
    std::string toString(std::string xVar);
};

Polynomial operator+(const Polynomial& P, const Polynomial& Q);
Polynomial operator-(const Polynomial& P, const Polynomial& Q);
Polynomial operator*(const Polynomial& P, const Polynomial& Q);
Polynomial operator*(const Z3& s, const Polynomial& P);
Polynomial operator*(Z3& s, const Polynomial& P);
Polynomial operator/(const Polynomial& P, const Z3& s);
void mod(const Polynomial& u, const Polynomial& v, Polynomial& q, Polynomial& r);
std::ostream& operator<<(std::ostream &o, const Polynomial &P);
std::istream& operator>>(std::istream& i, Polynomial& P);

#endif //BACACLION_POLYNOMIAL_H
