//Magda Wójtowicz
#include <iostream>
#include <cmath>
using namespace std;

int factorial(int k){
    int a = 1;
    for(int i = 2; i <= k; i++) a*=i;
    return a;
}

long double diffq(long double* X, long double*Y, int s, int k){

    if(X[s] == X[k]){
        int r = k-s;
        int p = s;
        while(X[p]==X[s]) p--;
        p++;
        long double h = Y[p+r]/factorial(r);
        return h;
    }
    long double d1 = diffq(X, Y, s+1, k);
    long double d2 = diffq(X,Y, s, k-1);
    long double u = X[k] - X[s];
    long double h = (d1-d2)/u;
    return h;

}

void Interpol()
{
    int N, M;
    cin >> M >> N;
    long double X[M];
    long double Y[M];
    long double T[N];
    for(int i = 0; i < M; i++){
        cin >> X[i];
    }
    for(int i = 0; i < M; i++){
        cin >> Y[i];
    }
     for(int i = 0; i < N; i++){
        cin >> T[i];
    }
    long double W[M];
    cout.precision(17);
    for(int i = 0; i < M; i++){
        W[i] = diffq(X, Y, 0, i);
    }
     for(int i = 0; i < M; i++){
        cout << fixed <<  W[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < N; i++){
        long double res = 0;
        long double a = 1;
        for(int j = 0; j < M; j++){
            long double b = W[j]*a;
            res+=b;
            long double c = T[i] - X[j];
            a*=c;
        }
        cout << fixed << res << " ";
    }



}

int main() {
    Interpol();
    return 0;
}
