#include <iostream>
#include "Test.h"
#include "OceniaczPojedynczyWybor.h"
#include "OceniaczWielokrotnyWybor.h"
#include "Oceniacz.h"
#include <vector>
#include "Pytanie.h"
int main() {
    int n = 1;
    Person Ania("Anna", "Nowak");
    std::vector<Pytanie>mathQs;
    for(int i = 0; i < n; i++)
    {
        Pytanie q(4);
        mathQs.push_back(q);
    }
    std::vector<Pytanie>engQs;
    for(int i = 0; i < n; i++)
    {
         Pytanie q(4);
         engQs.push_back(q);
    }
    Test mathTest(mathQs, Ania);
    Test engTest(engQs, Ania);

    OceniaczPojedynczyWybor opw;
    int m = mathTest.ocen(opw);

    OceniaczWielokrotnyWybor oww;
    int e = engTest.ocen(oww);
    std::cout << m << " " << e;
    return 0;
}
