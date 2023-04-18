// Magda Wójtowicz
// Created by Magda on 07.04.2023.
//

#ifndef BACACLION_Z3_H
#define BACACLION_Z3_H
#include <iostream>
class Z3 {
    short info;
public:
    Z3();
    explicit Z3(short _info);
    Z3(const Z3& _a);
    const short get_info() const;
    explicit operator short();
    explicit operator short() const;
    Z3 operator +=(const Z3& b);
    Z3 operator -=(const Z3& b);
    Z3 operator *=(const Z3& b);
    Z3 operator /=(const Z3& b);
    void operator=(const Z3& b);
    void operator=(const short& a);
    bool operator ==(const Z3& b);
};
Z3 operator+(const Z3& a, const Z3& b);
Z3 operator-(const Z3& a, const Z3& b);
Z3 operator*(const Z3& a, const Z3& b);
Z3 operator/(const Z3& a, const Z3& b);
std::ostream& operator<<(std::ostream &o, const Z3 &p);

#endif //BACACLION_Z3_H
