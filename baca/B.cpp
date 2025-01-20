//Magda Wójtowicz

#include <iostream>
#include <math.h>
void bisection(double (*f)(double), double &a, double &fa, double &b, double &fb, double &c, double &fc, int &M, double eps)
{
    int i;
    double e = b-a;
    for(i = 1; i <= M; i++)
    {
        e/=2;
        c = a+e;
        fc = f(c);
        if(e <= 0.1 || fabs(fc) < eps/10)
        {
            if(fa*fc < 0)
            {
                b = c;
                fb = fc;
            }
            else{
                a = c;
                fa = fc;
            }
            break;
        }   
        if(fa*fc < 0)
        {
            b = c;
            fb = fc;
        }
        else{
            a = c;
            fa = fc;
        }
    }
    M-=i;
}

double secant(double (*f)(double), double a, double b, double fa, double fb, int M, double eps){
    double c, fc, x;
    for(int i = 0; i < M; i++)
    {
        x = fb-fa;
        if(x == 0){
            b+=1e-15;
            x+=1e-15;
        }
        c = b - fb*((b-a)/(x));
        fc = f(c);
        if(fabs(fc) < eps/10)
             break;
        a = b; fa = fb;
        b = c; fb = fc; 
    }
    return c;
}

double findZero(
    double (*f)(double),  // funkcja ktĂłrej zera szukamy w [a, b] 
    double a,             // lewy koniec przedziaĹu
    double b,             // prawy koniec przedziaĹu
    int M,                // maksymalna dozwolona liczba wywoĹaĹ funkcji f
    double eps,           // spodziewana dokĹadnoĹÄ zera
    double delta          // wystarczajÄcy bĹÄd bezwzglÄdny wyniku
)
{
    double fa = f(a);
    double fb= f(b);
    if(fa == 0) return a;
    if(fb==0) return b;
    M-=2;
    if(fa*fb >= 0)
    {
        return secant(*f, a, b, fa, fb, M, eps);
    }
    double c, fc;
    bisection(*f, a, fa, b, fb, c, fc, M, eps);
    if(b-a < delta/10 || fabs(fc) < eps/10 || M==0)
        return c;
    return secant(*f, a, b, fa, fb, M, eps);
}

