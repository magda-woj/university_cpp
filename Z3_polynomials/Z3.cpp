// Magda Wójtowicz
// Created by Magda on 07.04.2023.
//
#include <iostream>
#include "Z3.h"

Z3::Z3()
{
    info = 0;
}
Z3::Z3(short _info){
    while(_info < 0) _info+=3;
    info = _info%3;
}
Z3::Z3(const Z3& _a){
    info = _a.info;
}
const short Z3::Z3::get_info() const{
    return info;
}

Z3::operator short(){
    return info;
}
Z3::operator short() const{
    return info;
}

Z3 Z3::operator +=(const Z3& b){
    Z3 c((this->info+b.info)%3);
    *this = c;
    return c;
}
Z3 Z3::operator -=(const Z3& b){
    short c = this->info-b.info;
    while(c < 0) c+=3;
    Z3 r(c%3);
    *this = r;
    return r;
}
Z3 Z3::operator *=(const Z3& b){
    Z3 r((this->info*b.info)%3);
    *this = r;
    return r;
}
Z3 Z3::operator /=(const Z3& b){
    if(b.info == 0){
        std::cout << "Dzielenie przez zero\n";
        return *this;
    }
    if(b.info == 1) return *this;
    return *this*=b;
}

void Z3::operator=(const Z3& b){
    info = b.info;
}

void Z3::operator=(const short& a){
    info = a;
}


bool Z3::operator ==(const Z3& b){
    return(info == b.info);
}

Z3 operator+(const Z3& a, const Z3& b){
    Z3 a_(a.get_info());
    return a_+=b;
}
Z3 operator-(const Z3& a, const Z3& b){
    Z3 a_(a.get_info());
    return a_-=b;
}
Z3 operator*(const Z3& a, const Z3& b){
    Z3 a_(a.get_info());
    return a_*=b;
}
Z3 operator/(const Z3& a, const Z3& b){
    Z3 a_(a.get_info());
    return a_/=b;
}

std::ostream& operator<<(std::ostream &o, const Z3 &p){
    o  << p.get_info();
    return o;
}
