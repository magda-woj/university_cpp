//Magda Wójtowicz
// Created by Magda on 15.06.2023.
//

#ifndef SPLINES_SOURCE_H
#define SPLINES_SOURCE_H


#include <vector>
using namespace std;

class spline {
public:
    spline(int n);
    void set_points(double x[], double y[]);
    double operator()(double z) const;

private:
    int numOfPoints;
    vector<double> h;
    vector<double> z;
    vector<double> X;
    vector<double> Y;

    double A(int i) const;

    double B(int i) const;

    double C(int i) const;
};


#endif //SPLINES_SOURCE_H
