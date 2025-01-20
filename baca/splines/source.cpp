//Magda Wójtowicz
// Created by Magda on 15.06.2023.
//

#include "source.h"
using namespace std;
spline::spline(int n) {
    numOfPoints = n;
    h.resize(n);
    z.resize(n);
    X.resize(n);
    Y.resize(n);
}

void spline::set_points(double x[], double y[]) {
    vector<double> b(numOfPoints);
    vector<double> u(numOfPoints);
    vector<double> v(numOfPoints);

    for(int i = 0; i < numOfPoints-1; i++){
        X[i] = x[i];
        Y[i] = y[i];

        h[i] = x[i+1] - x[i];

        b[i] = 6*(y[i+1] - y[i])/h[i];

    }
    X[numOfPoints-1] = x[numOfPoints-1];
    Y[numOfPoints-1] = y[numOfPoints-1];

    u[1] = 2*(h[0] + h[1]);
    v[1] = b[1] - b[0];

    for(int i = 2; i < numOfPoints-1; i++){
        u[i] = 2*(h[i-1] + h[i]) - h[i-1]*h[i-1] /u[i-1];
        v[i] = b[i] - b[i-1]  - h[i-1]*v[i-1]/u[i-1];
    }
    z[numOfPoints-1] = 0;
    for(int i = numOfPoints-2; i >= 1; i--){
        z[i] = (v[i] - h[i]*z[i+1])/u[i];
    }
    z[0] = 0;


}
double spline::A(int i) const{
    return 1/(6*h[i]) * (z[i+1]-z[i]);
}

double spline::B(int i) const{
    return z[i]/2;
}

double spline::C(int i) const{
    return -h[i]/6 * (z[i+1]+2*z[i]) + 1/h[i]*(Y[i+1]-Y[i]);
}
double spline::operator()(double z) const {
    int i = 0;
    while (i < numOfPoints && z >= X[i]) {
        i++;
    }
    i--;
    return (Y[i] + (z-X[i])*(C(i) + (z-X[i])*(B(i) + (z-X[i])*A(i))));
}
