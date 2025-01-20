//Magda Wójtowicz
#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>
using namespace std;

float solveQuadratic(float a, float b, float c)
{
    float x1,x2;
    float d = b*b-4*a*c;
    if (d > 0) {
        x1 = (-b+sqrt(d))/(2*a);
        x2 = (-b-sqrt(d))/(2*a);
        if((x1 !=0)) 
            return x1;
        if(x2 != 0)
            return x2;
    }
    else if (d == 0) {
        x1 = -b/(2*a);  
        if((x1 <= -1) || (x1 > 0 && x1 <= 1))
            return x1;
    }
    return 0;
}

int main()
{
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cout.precision(10);
        float P, S;
        float a, b, c, pm, sm, am, bm, cm;
        int *pe = new int;
        int* se = new int;
        int ae, be, ce;
        cin >> P >> S;
        pm = frexpf(P, pe);
        sm = frexpf(S, se);        
        if(pm == 0)
        {
            {a = 0; b = 0; c = 0;}
        }
        be = *pe/3;
        bm = cbrt(pm*pow(2, *pe-3*be));
        float q = solveQuadratic(1, 1 - (sm/bm)*pow(2, *se-be), 1);
        if(q == 0) {a = 0; b = 0; c = 0;}
        else
        {
            b = bm*pow(2,be);
            a = b/q;
            c = b*q;
            if(a < c) swap(a,c);
            if(!(a*b*c) == pm*pow(2,*pe)){a = 0; b = 0; c = 0;}

        }
        cout << scientific << a << " " << b << " " << c << " " << endl;
    }
}
