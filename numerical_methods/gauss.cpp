//Magda Wójtowicz
#include <iostream>
#include "vectalg.h"
using namespace std;

Vector scales(const Matrix& A)
{
    int n = A.size(); 
    Vector x(n);
    Vector a(n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            a[j] = A(i,j);
        }
        x[i] = a.max_norm();
    }
    return x;
}
void swapRows(Matrix &A, Vector &b, int i, int j)
{
    for(int k = 0 ; k < A.size(); k++){
        std::swap(A(i, k), A(j, k));
    }
    std::swap(b[i], b[j]);
}
void choose(Matrix& A, Vector &b, const Vector& scales, int k)
{
    int max = k;
    for(int i = k; i < A.size(); i++)
    {
        if(std::abs(A(i, k))/scales[i] > std::abs(A(max, k))/scales[max]) 
            max = i;
    }
    if(max != k) swapRows(A, b, k, max);
}

void scaledSubstraction(Matrix&A, Vector &b, int i, int j, double r)
{
    for(int k = 0; k < A.size(); k++)
    {
        A(j, k) = A(j, k)-(r*A(i,k));
        int x = 0;
    }
    b[j] = b[j]-(r*b[i]);

}


void add(Vector &x, const Vector&y)
{
    int n = x.size();
    for(int i = 0; i < n; i++)
    {
        x[i] += y[i];
    }
    return;
}
void Gaussian(Matrix& A, Vector &b, Vector & x, const Vector& scales)
{
    int n = A.size();
    for(int i  = 0; i < n; i++)
    {
        choose(A, b, scales, i);
        for(int j = i+1; j < n; j++)
        {
            double r = A(j,i)/A(i,i);
            scaledSubstraction(A, b, i, j, r);
        }
    }

    for(int i = n-1; i >= 0; i--)
    {
        double y=b[i];
        for(int j = i+1; j < n; j++)
        {
            y -= A(i,j)*x[j];
        }
        x[i] = y/A(i,i);
    }
}

Vector solveEquations(
        const Matrix & A,   // Macierz
        const Vector & b,   // Wektor 
        double  eps         // dopuszczalny błąd 
)
{
    int n = A.size();
    Vector x(n);
    Vector s = scales(A);
 //   cout << s << endl;
    Matrix copyA = A;
    Vector copyb = b;
    Gaussian(copyA, copyb, x, s);

 //   cout << x << endl;
    
    while(residual_vector(A, b, x).max_norm() >= eps)
    {
        double f = residual_vector(A, b, x).max_norm();        copyA = A;
        copyb = residual_vector(A, b, x);
        Vector e(n);
        Gaussian(copyA, copyb, e, s);
      //  cout << e << endl;
        add(x, e);
       // cout << x << endl;
    }

    return x;
}


