//windows console polynomial calculator using karatsuba multiplication algorithm
#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;

void com()
{
    system("cls");
    cout << "Bledny input. Nacisnij dowolny klawisz aby kontynuowac.";
    getch();
    system("cls");
}

class polynomial{
private:
    float *coeff;
public:
    int deg;
    polynomial(int _deg)
    {
        deg = _deg;
        coeff = new float[_deg+1];
        for(int i = 0; i <= deg; i++)
            coeff[i] = 0;
    };
    ~polynomial()
    {
        delete[] coeff;
        coeff = NULL;
    };

    void print()
    {
        if(deg == 0){
            cout << coeff[0];
            return;
        }
        if(deg == 1)
            cout << coeff[1] << "x";
        else{
            cout << coeff[deg] << "x^" << deg;
            for(int i = deg-1; i > 1; --i)
            {
            if(coeff[i] > 0) cout << " + " << coeff[i] << "x^" << i;
                else if(coeff[i] < 0) cout << " - " << abs(coeff[i]) << "x^" << i;
            }
            if(coeff[1] > 0) cout << " + " << coeff[1] << "x";
            else if(coeff[1] < 0) cout << " - " << abs(coeff[1]) << "x";
        }
        if(coeff[0] > 0) cout << " + " << coeff[0];
        else if(coeff[0] < 0) cout << " - " << abs(coeff[0]);
    };

void randomCoeffs(){
    for(int i = 0; i<= deg; i++){
        coeff[i] =  rand()%201 - 100;
    }
}

void askCoeffs()
{
    cin.clear();
    cin.sync();
    cout << "Chce wylosowac wspolczynniki - 'R' " << endl << "Chce wprowadzic wspolczynniki - dowolny klawisz ";
    char z = getch();
    if(z=='r' || z=='R'){
        srand(time(NULL));
        randomCoeffs();
        system("cls");
        return;
    }
    float c;
    for(int i = deg; i >= 0; --i)
    {
        do
        {
            system("cls");
            cin.clear();
            cin.sync();
            cout << "Podaj wpolczynnik wielomianu przy potedze " << i << ": ";
            cin >> c;
            if(!cin.good())
            {
                com();
                continue;
            }
        }
        while(!cin.good());
        coeff[i] = c;
        cin.clear();
        cin.sync();
        cout << "Wcisnij 'Z' by wyzerowac pozostale wspolczynniki ";
        char z = getch();
        if(z=='Z' || z=='z')
        {
            system("cls");
            return;
        }
        system("cls");
    }
}

void add(polynomial &Q, polynomial &R)
{
    if(deg < Q.deg) return Q.add(*this, R);
    for(int i = 0; i <= Q.deg; i++)
    {
        R.coeff[i] = coeff[i] + Q.coeff[i];
    }
    for(int i = Q.deg+1; i <= deg; i++)
    {
        R.coeff[i] = coeff[i];
    }
}

void substract(polynomial &Q, polynomial &R)
{
    if(deg >= Q.deg)
    {
        for(int i = 0; i <= Q.deg; i++)
        {
            R.coeff[i] = coeff[i] - Q.coeff[i];
        }
        for(int i = Q.deg+1; i <= deg; i++)
        {
            R.coeff[i] = coeff[i];
        }
        return;
    }
        for(int i = 0; i <= deg; i++)
        {
            R.coeff[i] = coeff[i] - Q.coeff[i];
        }
        for(int i = deg+1; i <= Q.deg; i++)
        {
            R.coeff[i] = -Q.coeff[i];
        }
        return;
}

void multiply(polynomial &Q, polynomial &R)
{
    if(deg>2 && deg==Q.deg){
        this->multiplyKaratsuba(Q, R);
        return;
    }
    for (int i = 0; i<=R.deg; i++)
    R.coeff[i] = 0;
  
   for (int i=0; i<=deg; i++)
   {
     for (int j=0; j<=Q.deg; j++)
         R.coeff[i+j] += coeff[i]*Q.coeff[j];
   }
}


void multiplyKaratsuba(polynomial &Q, polynomial &R)
{
    if(deg <= 2 || Q.deg <= 2)
    {
        this->multiply(Q, R);
        return;
    }
    polynomial P1(deg/2);
    polynomial P2(deg/2);
    polynomial P3(deg/2);
    polynomial Q1(deg/2);
    polynomial Q2(deg/2);
    polynomial Q3(deg/2);
    polynomial P1Q1(P1.deg+Q1.deg);
    polynomial P2Q2(P2.deg+Q2.deg);
    polynomial P3Q3(P3.deg+Q3.deg);
    int h;
    if(deg%2 == 0){
    h = deg/2;
    P2.coeff[h] = coeff[deg];
    P3.coeff[h] = coeff[deg];
    Q2.coeff[h] = Q.coeff[deg];
    Q3.coeff[h] = Q.coeff[deg];
    }
    else h = deg/2+1;
    for(int i = 0; i < h; i++)
    {
        P1.coeff[i] = coeff[i];
        P2.coeff[i] = coeff[i+h];
        P3.coeff[i] = P1.coeff[i] + P2.coeff[i];
        Q1.coeff[i] = Q.coeff[i];
        Q2.coeff[i] = Q.coeff[i+h];
        Q3.coeff[i] = Q1.coeff[i] + Q2.coeff[i];
    }
    P1.multiplyKaratsuba(Q1, P1Q1);
    P2.multiplyKaratsuba(Q2, P2Q2);
    P3.multiplyKaratsuba(Q3, P3Q3);
     for(int i = 0; i <= P1Q1.deg; i++)
        R.coeff[i] = P1Q1.coeff[i];
    for(int i = 0; i <= P3Q3.deg; i++)
        R.coeff[h+i] = R.coeff[h+i] + P3Q3.coeff[i] - P1Q1.coeff[i] - P2Q2.coeff[i];
    for(int i = 0; i <= P2Q2.deg; i++)
        R.coeff[R.deg-P2Q2.deg+i] += P2Q2.coeff[i];
    return;
}

float horner(float x)
{
    float h = coeff[deg];
    for(int i = deg-1; i >= 0; --i)
    {
        h = h*x + coeff[i];
    }
    return h;
}
};


polynomial askDegree()
{
    int deg;
    do
    {
        cin.clear();
        cin.sync();
        cout << "Podaj stopien wielomianu: ";
        cin >> deg;
        system("cls");
        if(!cin.good())
        {
            com();
            continue;
        }
        if(deg < 0)
        {
            com();
            continue;
        }
    }
    while(!cin.good()||deg < 0);
    polynomial R(deg);
    return R;
}


float askX()
{
    float x;
    do
    {
        cin.clear();
        cin.sync();
        cout << "W jakim punkcie chcesz obliczyc wartosc wielomianu? ";
        cin >> x;
        system("cls");
        if(!cin.good())
        {
            com();
            continue;
        }
    }
    while(!cin.good());
    return x;
}

char askQ()
{   
    cout << "Czy chcesz wykonac nastepna operacje na tym wielomianie? T/t - tak, inny klawisz - nie ";
    char z = getch();
    return z;
}

void nextRound(polynomial &P)
{
    system("cls");
    char q = 'T';
    cout << "Kalkulator wielomianowy" << endl;
    cout << "Wybierz operacje na wielomianie ";
    P.print();
    cout << ":" << endl;
    cout << endl << "W - obliczanie wartosci wielomianu" << endl
    << "D - dodawanie wielomianu" << endl << "O - odjecie wielomianu" << endl << "P - odjecie od wielomianu" << endl << "M - pomnozenie przez wielomian" << endl
    << "lub nacisnij klawisz esc aby zakonczyc prace programu" << endl;

    char z = getch();
    system("cls");

    switch(z)
    {
        case 'w': case 'W':
        {
            float x = askX();
            float y = P.horner(x);
            cout << "Wartosc wielomianu: ";
            P.print();
            cout << " w punkcie " << x << " wynosi " << y << endl;
            getch();
            break;
        }
        case 'd': case 'D':
        {
            cout << "Drugi skladnik: ";
            polynomial Q = askDegree();
            Q.askCoeffs();
            cout << "(";
            P.print();
            cout << ") + (";
            Q.print();
            cout << ") = ";
            polynomial R(max(P.deg, Q.deg));
            P.add(Q, R);
            cout << endl;
            R.print();
            cout << endl;
            char q = askQ();
            if(q == 't' || q=='T') nextRound(R);
            break;
        }
        case 'o': case 'O':
        {
            cout << "Odjemnik: ";
            polynomial Q = askDegree();
            Q.askCoeffs();
            cout << "(";
            P.print();
            cout << ") - (";
            Q.print();
            cout << ") = ";
            polynomial R(max(P.deg, Q.deg));
            P.substract(Q, R);
            cout << endl;
            R.print();
            cout << endl;
            char q = askQ();
            if(q == 't' || q=='T') nextRound(R);
            break;
        }
        case 'p': case 'P':
        {
            cout << "Odjemna: ";
            polynomial Q = askDegree();
            Q.askCoeffs();
            cout << "(";
            Q.print();
            cout << ") - (";
            P.print();
            cout << ") = ";
            polynomial R(max(P.deg, Q.deg));
            Q.substract(P, R);
            cout << endl;
            R.print();
            cout << endl;
            char q = askQ();
            if(q == 't' || q=='T') nextRound(R);
            break;
        }
         case 'm': case 'M':
        {
            cout << "Drugi czynnik: ";
            polynomial Q = askDegree();
            Q.askCoeffs();
            cout << "(";
            P.print();
            cout << ") * (";
            Q.print();
            cout << ") = ";
            polynomial R(P.deg + Q.deg);
            P.multiply(Q, R);
            cout << endl;
            R.print();
            polynomial S(P.deg+Q.deg);
            cout << endl;
            char q = askQ();
            if(q == 't' || q=='T')  nextRound(R);
            break;
        }
        case 27:
                system("cls");
                exit(0);

        default:
        cout << "Bledna opcja. Nacisnij dowolny klawisz, aby kontynuowac.";
        getch();
        break;
        }
        system("cls");
}


void firstRound()
{
    do{
    cout << "Kalkulator wielomianowy" << endl;
    cout << "Wybierz operacje: " << endl << "W - obliczanie wartosci wielomianu" << endl
    << "D - dodawanie wielomianow" << endl << "O - odejmowanie wielomianow" << endl << "M - mnozenie wielomianow" << endl
    << "lub nacisnij klawisz esc aby zakonczyc prace programu" << endl;

    char z = getch();
    system("cls");

    switch(z)
    {
        case 'w': case 'W':
        {
            polynomial P = askDegree();
            P.askCoeffs();
            float x = askX();
            float y = P.horner(x);
            cout << "Wartosc wielomianu: ";
            P.print();
            cout << " w punkcie " << x << " wynosi " << y << endl;
            getch();
            break;
        }
        case 'd': case 'D':
        {
            cout << "Pierwszy skladnik: ";
            polynomial P = askDegree();
            P.askCoeffs();
            cout << "Drugi skladnik: ";
            polynomial Q = askDegree();
            Q.askCoeffs();
            cout << "(";
            P.print();
            cout << ") + (";
            Q.print();
            cout << ") = ";
            polynomial R(max(P.deg, Q.deg));
            P.add(Q, R);
            cout << endl;
            R.print();
            cout << endl;
            char q = askQ();
            if(q == 't' || q=='T') nextRound(R);
            break;
        }
        case 'o': case 'O':
        {
            cout << "Odjemna: ";
            polynomial P = askDegree();
            P.askCoeffs();
            cout << "Odjemnik: ";
            polynomial Q = askDegree();
            Q.askCoeffs();
            cout << "(";
            P.print();
            cout << ") - (";
            Q.print();
            cout << ") = ";
            polynomial R(max(P.deg, Q.deg));
            P.substract(Q, R);
            cout << endl;
            R.print();
            cout << endl;
            char q = askQ();
            if(q == 't' || q=='T')  nextRound(R);
            break;
        }
        case 'm': case 'M':
        {
            cout << "Pierwszy czynnik: ";
            polynomial P = askDegree();
           P.askCoeffs();
            cout << "Drugi czynnik: ";
            polynomial Q = askDegree();
            Q.askCoeffs();
            cout << "(";
            P.print();
            cout << ") * (";
            Q.print();
            cout << ") = ";
            polynomial R(P.deg + Q.deg);
            P.multiply(Q, R);
            cout << endl;
            R.print();
            cout << endl;
            char q = askQ();
            if(q == 't' || q=='T')  nextRound(R);
            break;

        }
        case 27:
            system("cls");
            exit(0);

        default:
        cout << "Bledna opcja. Nacisnij dowolny klawisz, aby kontynuowac.";
        getch();
        break;
        }
        system("cls");
    }
    while(true);
}


int main(){
    firstRound();
    return 0;
}
