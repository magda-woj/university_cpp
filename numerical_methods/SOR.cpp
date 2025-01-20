//Magda Wójtowicz
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
// Jeżeli odkomentujemy poniższą linię to indeksy (assert) nie będą sprawdzane
// #define  NDEBUG
using namespace std;

void SOR(const vector<vector<double>> &A, const vector<double>&diag, const vector<double> &b, vector<double> & x0, int N, int M, int L, double w ) {// Jacobi
    cout.precision(16);
    for(int iter=0; iter < L; iter++) {
        for (int i = 0; i < N; i++) {
            auto s = b[i];
            for(int m = max(0, i-M); m < i; m++) {
                double h = A[M-fabs(i-m)][m];
                s -= h*x0[m];
            }
            for (int m = i + 1; m <= min(i+M, N-1); m++) {
                double h = A[M-fabs(i-m)][i];
                s -= h*x0[m];
            }
            x0[i] = (1-w) * x0[i] + w* s / diag[i];
        }
    }
    for(auto i:x0) cout << scientific << i << endl;
}
int main() {
    int N, M, L;
    cin >> N >> M;
    vector<vector<double>> input;
    double a, w;
    vector<double> diag, x, y;
    std::string line;
    std::getline(cin, line);
    for(int i = 0; i < M; i++){
        line = "";
        vector<double>  s;
        std::getline(cin, line);
        std::istringstream iss(line);
        while ( iss >> a) {    
        s.push_back(a);
        }
        input.push_back(s);
    }
    for(int i = 0; i< N; i++)
    {
        cin >> a;
        diag.push_back(a);
    }
    for(int i = 0; i< N; i++)
    {
        cin >> a;
        y.push_back(a);
    }
    for(int i = 0; i< N; i++)
    {
        cin >> a;
        x.push_back(a);
    }
    cin>> w >> L;
    SOR(input, diag, y, x, N, M, L, w);
    return 0;
}
