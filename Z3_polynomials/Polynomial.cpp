// Magda Wójtowicz
// Created by Magda on 07.04.2023.
//
#include <string>
#include <iostream>
#include "Polynomial.h"
#include "Z3.h"
struct Z3Node{
    Z3 a;
    Z3Node* next;

    Z3Node(short info){
        a = Z3(info);
        next = nullptr;
    }
};
struct Z3List{
    Z3Node* head;
    Z3List()
    {
        head = nullptr;
    }
    void insert(Z3Node* a)
    {
        a->next = head;
        head = a;
    }
};
Polynomial::Polynomial(){
    deg = 0;
    coeffs = new Z3[deg+1];
    coeffs[0] = Z3(0);
}

Polynomial::Polynomial(unsigned int _deg, Z3 _coeffs[]){
    deg = _deg;
    coeffs = new Z3[deg+1];
    for(int i = 0; i <= deg; i++)
    {
        coeffs[i] = _coeffs[i];
    }
    this->resize();
}
Polynomial::Polynomial(const Polynomial& O){
    deg = O.deg;
    coeffs = new Z3[deg+1];
    for(int i = 0; i <= deg; i++)
    {
        coeffs[i] = O.coeffs[i];
    }
    this->resize();
}

Polynomial::~Polynomial(){
    delete[] coeffs;
    coeffs = nullptr;
}
Z3& Polynomial::operator[](int i){
    if (i >= 0 && i <= deg) return coeffs[i];
    std::cout << "Niepoprawny indeks wielomianu\n";
    return coeffs[0];
}

Z3& Polynomial::operator[](int i) const{
    if (i >= 0 && i <= deg) return coeffs[i];
    std::cout << "Niepoprawny indeks wielomianu\n";
    return coeffs[0];
}


void Polynomial::resize(){

    unsigned int newDeg = deg;
    while(coeffs[newDeg].get_info()==0 && newDeg>0)
        newDeg--;
    if(newDeg == deg)
        return;
    Z3 newCoeffs[newDeg+1];
    for(int i = 0; i <= newDeg; i++)
    {
        newCoeffs[i] = coeffs[i];
    }
    Polynomial _P(newDeg, newCoeffs);
    *this = _P;
    return;
}

Polynomial Polynomial::operator +=(const Polynomial& Q){

    if(deg >= Q.deg)
    {

        Z3 resultCoeffs[deg+1];
        for(int i = 0; i <= Q.deg; i++)
        {
            resultCoeffs[i] = coeffs[i] + Q.coeffs[i];
        }
        for(int i = Q.deg+1; i <= deg; i++)
        {
            resultCoeffs[i] = coeffs[i];
        }
        Polynomial R(deg, resultCoeffs);
        R.resize();
        *this = R;
        return R;
    }
    Z3 resultCoeffs[Q.deg+1];
    for(int i = 0; i <= deg; i++)
    {
        resultCoeffs[i] = coeffs[i] + Q.coeffs[i];
    }
    for(int i = deg+1; i <= Q.deg; i++)
    {
        resultCoeffs[i] = Q.coeffs[i];
    }
    Polynomial R(Q.deg, resultCoeffs);
    R.resize();
    *this = R;
    return R;
}

Polynomial Polynomial::operator -=(const Polynomial& Q){

    if(deg >= Q.deg)
    {
        Z3 resultCoeffs[deg+1];
        for(int i = 0; i <= Q.deg; i++)
        {
            resultCoeffs[i] = coeffs[i] - Q.coeffs[i];
        }
        for(int i = Q.deg+1; i <= deg; i++)
        {
            resultCoeffs[i] = coeffs[i];
        }
        Polynomial R(deg, resultCoeffs);
        R.resize();
        *this = R;
        return R;
    }
    Z3 resultCoeffs[Q.deg+1];
    for(int i = 0; i <= deg; i++)
    {
        resultCoeffs[i] = coeffs[i] - Q.coeffs[i];
    }
    Z3 x(0);
    for(int i = deg+1; i <= Q.deg; i++)
    {
        resultCoeffs[i] = x-Q.coeffs[i];
    }
    Polynomial R(Q.deg, resultCoeffs);
    R.resize();
    *this = R;
    return R;
}
Polynomial Polynomial::operator *=(const Polynomial& Q){
    unsigned int rdeg = deg+Q.deg;
    Z3 resultCoeffs[rdeg+1];
    for(int i = 0; i <= rdeg; i++)
        resultCoeffs[i] = Z3(0);
    for (int i = 0; i <= deg; i++)
    {
        for (int j = 0; j <= Q.deg; j++) {
            Z3 z = coeffs[i] * Q.coeffs[j];
            resultCoeffs[i + j] = resultCoeffs[i+j] + z;
        }
    }
    Polynomial R(rdeg, resultCoeffs);
    R.resize();
    *this = R;
    return R;
}
Polynomial Polynomial::operator *=(const Z3& s){
    Z3 resultCoeffs[deg+1];
    for(int i = 0; i <= deg; i++)
        resultCoeffs[i] = s*coeffs[i];
    Polynomial R(deg, resultCoeffs);
    R.resize();
    *this = R;
    return R;
}
Polynomial Polynomial::operator *=(Z3& s){

    Z3 resultCoeffs[deg+1];
    for(int i = 0; i <= deg; i++)
        resultCoeffs[i] = s*coeffs[i];
    Polynomial R(deg, resultCoeffs);
    R.resize();
    *this = R;
    return R;
}
Polynomial Polynomial::operator /=(const Z3& s){
    if(s.get_info()==0){
        std::cout << "Dzielenie przez zero\n";
        return *this;
    }
    Z3 resultCoeffs[deg+1];
    for(int i = 0; i <= deg; i++)
        resultCoeffs[i] = coeffs[i]/s;
    Polynomial R(deg, resultCoeffs);
    R.resize();
    *this = R;
    return R;
}
void Polynomial::operator=(const Polynomial& oP){
    if(coeffs) delete[] coeffs;
    deg = oP.deg;
    coeffs=new Z3[deg+1];
    for(int i = 0; i <= deg; i++)
    {
        coeffs[i] = oP.coeffs[i];
    }
    this->resize();
}

unsigned int Polynomial::degree() const{
    return deg;
}
std::string Polynomial::toString(std::string xVar){
    this->resize();
    if(deg == 0) return std::to_string(coeffs[0].get_info());
    std::string res = "";
    if(coeffs[0].get_info()!=0) res = res + std::to_string(coeffs[0].get_info()) + "+";
    for(int i = 1; i < deg; i++)
    {
        if(coeffs[i].get_info() != 0)
        {
            res = res + std::to_string((int)coeffs[i].get_info()) + "*" + xVar + "^" +std::to_string(i) + "+";

        }
    }
    if(coeffs[deg].get_info() != 0)
    {
        res = res + std::to_string((int)coeffs[deg].get_info()) + "*" + xVar + "^" + std::to_string(deg);

    }
    return res;
}

Polynomial operator+(const Polynomial& P, const Polynomial& Q){

    if(P.degree() >= Q.degree())
    {
        Polynomial _P(P);
        return _P+=Q;
    }
    else{
        return Q+P;
    }
}
Polynomial operator-(const Polynomial& P, const Polynomial& Q){

    Polynomial _P(P);
    return _P-=Q;
}
Polynomial operator*(const Polynomial& P, const Polynomial& Q){

    Polynomial _P(P);
    return _P*=Q;
}
Polynomial operator*(const Z3& s, const Polynomial& P){

    Polynomial _P(P);
    return _P*=s;
}
Polynomial operator*(Z3& s, const Polynomial& P){

    Polynomial _P(P);
    return _P*=s;
}
Polynomial operator/(const Polynomial& P, const Z3& s){

    Polynomial _P(P);
    return _P/=s;
}
void mod(const Polynomial& u, const Polynomial& v, Polynomial& q, Polynomial& r){
    if(v.degree() == 0){
        if(v[0].get_info() == 0) {
            std::cout << "Dzielenie przez zero\n";
            return;
        }
        Z3 result[1];
        result[0] = Z3(0);
        r = Polynomial(0, result);
        q = u/v[0];
        return;
    }
    if(v.degree() > u.degree()) {
        Z3 result[1];
        result[0] = Z3(0);
        q = Polynomial(0, result);
        r = u;
        return;
    }
    unsigned int i = u.degree()-v.degree();
    unsigned int d = v.degree();
    Z3 qcoeffs[i+1];
    for(int j = 0; j < i; j++) qcoeffs[j] = 0;
    qcoeffs[i] = 1;
    q = Polynomial(i, qcoeffs);
    r = u;
    Polynomial help = v;
    while(r.degree() >= v.degree()){
        Z3 helpCoeffs[i+1];
        q[i] = r[d+i]/v[d];
        helpCoeffs[i] = q[i];
        for(int j = 0; j < i; j++) helpCoeffs[j] = 0;
        Polynomial help2(i, helpCoeffs);
        help=v*help2;
        r-=help;
        i = r.degree()-v.degree();
    }
    return;
}

std::ostream& operator<<(std::ostream &o, const Polynomial &P){

    Polynomial _P(P);
    _P.resize();
    o  << "{";
    for(int i = 0; i < P.degree(); i++)
    {
        o << _P[i] << ",";
    }
    o << _P[P.degree()] << "}";
    return o;
}

std::istream& operator>>(std::istream& i, Polynomial& P)
{
    char c;
    while(c!='{')
    {
        i >> c;
    }
    Z3List list;
    unsigned int deg = -1;
    while(c!='}')
    {
        deg++;
        short info;
        i >> info;
        Z3Node* a = new Z3Node(info);
        list.insert(a);
        i >> c;
    }
    Z3 coeffs[deg+1];
    Z3Node* a = list.head;
    for(int j = deg; j >= 0; j--)
    {
        coeffs[j] = a->a;
        a = a->next;
    }
    Polynomial _P = Polynomial(deg, coeffs);
    _P.resize();
    P = _P;
    return i;
}