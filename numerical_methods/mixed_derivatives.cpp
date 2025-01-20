//Magda Wójtowicz
#include<iostream>
#include<cmath>
#include "funkcja.h"

using namespace std;

class Jet{
    public:
    double f;
    double fx;
    double fy;
    double fxx;
    double fxy;
    double fyy;

    Jet(){
        f = 0;
        fx =0;
        fy = 0;
        fxx=0;
        fxy=0;
        fyy=0;
    }

    Jet(const Jet& O){
        f = O.f;
        fx = O.fx;
        fy = O.fy;
        fxx = O.fxx;
        fxy = O.fxy;
        fyy = O.fyy;
    }

     Jet(Jet& O){
        f = O.f;
        fx = O.fx;
        fy = O.fy;
        fxx = O.fxx;
        fxy = O.fxy;
        fyy = O.fyy;
    }

    void operator=(const Jet& O){
        f = O.f;
        fx = O.fx;
        fy = O.fy;
        fxx = O.fxx;
        fxy = O.fxy;
        fyy = O.fyy;
    }


};
Jet operator -(const Jet&L){
        Jet result;
        result.f = -L.f;
        result.fx = -L.fx;
        result.fy = -L.fy;
        result.fxx = -L.fxx;
        result.fxy = -L.fxy;
        result.fyy = -L.fyy;
        return result;
    }

Jet operator +(const Jet& L, const Jet& P){
        Jet result;
        result.f = L.f+P.f;
        result.fx = L.fx+P.fx;
        result.fy = L.fy+P.fy;
        result.fxx = L.fxx+P.fxx;
        result.fxy = L.fxy+P.fxy;
        result.fyy = L.fyy+P.fyy;
        return result;
    }
Jet operator -(const Jet& L, const Jet& P){
        Jet result;
        result.f = L.f-P.f;
        result.fx = L.fx-P.fx;
        result.fy = L.fy-P.fy;
        result.fxx = L.fxx-P.fxx;
        result.fxy = L.fxy-P.fxy;
        result.fyy = L.fyy-P.fyy;
        return result;
    }
    Jet operator *(const Jet& L, const Jet& P){
        Jet result;
        result.f = L.f*P.f;
        result.fx = L.fx*P.f + L.f*P.fx;
        result.fy = L.fy*P.f + L.f*P.fy;
        result.fxx = L.fxx*P.f + 2*L.fx*P.fx + L.f*P.fxx;
        result.fyy = L.fyy*P.f + 2*L.fy*P.fy + L.f*P.fyy;
        result.fxy = L.fxy*P.f + L.fx*P.fy + L.fy*P.fx + L.f*P.fxy;
        return result;
    }
    Jet operator /(const Jet& L, const Jet& P){
        Jet result;
        double h =  L.f/P.f;
        double hx = (L.fx - (h*P.fx))/P.f;
        double hy = (L.fy - (h*P.fy))/P.f;
        result.f = h;
        result.fx = hx;
        result.fy = hy;
        result.fxx = (L.fxx - 2*P.fx*hx - h*P.fxx)/P.f;
        result.fyy = (L.fyy - 2*P.fy*hy - h*P.fyy)/P.f; //check?
        result.fxy = (L.fxy - P.fx*hy - P.fy*hx - h*P.fxy)/P.f;
        return result;
    }
  
    Jet operator +(const Jet&L, const double& a){
        Jet result(L);
        result.f+=a;
        return result;
    }
    Jet operator -(const Jet&L,const double& a){
        Jet result(L);
        result.f-=a;
        return result;
    }
    Jet operator *(const Jet&L,const double& a){
        Jet result(L);
        result.f*=a;
        result.fx*=a;
        result.fy*=a;
        result.fxx*=a;
        result.fxy*=a;
        result.fyy*=a;        
        return result;
    }
    Jet operator /(const Jet&L,const double& a){
        Jet result(L);
        result.f/=a;
        result.fx/=a;
        result.fy/=a;
        result.fxx/=a;
        result.fxy/=a;
        result.fyy/=a;        
        return result;
    }

     Jet operator +(const double& a, const Jet&L){
        return L+a;
     }
    Jet operator -(const double& a, const Jet&L){
        return -L+a;
    }
    Jet operator *(const double& a, const Jet&L){
        return L*a;  
    }
    Jet operator /(const double& a, const Jet&L){
        Jet result;
        result.f = a;
        return result/L;
    }
    // Jet operator +(const Jet&L, const int& a){
    //     Jet result;
    //      result.f = L.f+a;
    //     result.df = L.df;
    //     return result;
    // }
    // Jet operator -(const Jet&L,const int& a){
    //     Jet result;
    //     result.f = L.f-a;
    //     result.df = L.df;
    //     return result;
    // }
    // Jet operator *(const Jet&L,const int& a){
    //     Jet result;
    //     result.f = L.f*a;
    //     result.df = L.df*a;
    //     return result;
    // }
    // Jet operator /(const Jet&L,const int& a){
    //     Jet result;
    //     result.f = L.f/a;
    //     result.df = L.df/a;
    //     return result;
    // }

Jet sin(const Jet& v){
    Jet result;
    result.f = sin(v.f);
    result.fx = v.fx*cos(v.f);
    result.fy = v.fy*cos(v.f);
    result.fxx = v.fxx*cos(v.f) - v.fx*v.fx*sin(v.f);
    result.fyy = v.fyy*cos(v.f) - v.fy*v.fy*sin(v.f);
    result.fxy = v.fxy*cos(v.f) - v.fx*v.fy*sin(v.f);
    return result;
    } 

Jet cos(const Jet& v){
    Jet result;
    result.f = cos(v.f);
    result.fx = -v.fx*sin(v.f);
    result.fy = -v.fy*sin(v.f);
    result.fxx = -v.fxx*sin(v.f) - v.fx*v.fx*cos(v.f);
    result.fyy = -v.fyy*sin(v.f) - v.fy*v.fy*cos(v.f);
    result.fxy = -v.fxy*sin(v.f) - v.fx*v.fy*cos(v.f);
    return result;
    }

Jet exp(const Jet&v){
    Jet result;
    result.f = exp(v.f);
    result.fx = v.fx*exp(v.f);
    result.fy = v.fy*exp(v.f);
    result.fxx = exp(v.f)*(v.fx*v.fx + v.fxx);
    result.fyy = exp(v.f)*(v.fy*v.fy + v.fyy);
    result.fxy = exp(v.f)*(v.fx*v.fy + v.fxy);
    return result;
} 

int main(){
    int M;
    cin >> M;
    cout.precision(15);
    for(int i = 0; i < M; i++){
        double x, y;
        cin >> x >> y;
        Jet X;
        X.f = x;
        X.fx = 1;
        X.fy = 0;
        X.fxx = 0;
        X.fxy = 0;
        X.fyy = 0;

        Jet Y;
        Y.f = y;
        Y.fx = 0;
        Y.fy = 1;
        Y.fxx = 0;
        Y.fxy = 0;
        Y.fyy = 0;
        Jet R = funkcja(X, Y);

        cout << R.f << " " << R.fx << " "  << R.fy << " "  << R.fxx << " "  << R.fxy << " "  << R.fyy << " "  << endl;
    }
}
