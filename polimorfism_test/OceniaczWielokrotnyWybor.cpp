//
// Created by Magda on 14.04.2023.
//

#include "OceniaczWielokrotnyWybor.h"

int OceniaczWielokrotnyWybor::ocenPytanie(const Pytanie& p) const {
    if(p.nOfBad() == 0)
        return 2;
    if(p.getBad_Marked() != 0)
    {
        int x = p.getBad_Marked();
        return -1;
    }
  //      return -1;
    if(p.nOfUnmarked() == p.nOfAns())
        return 0;
    if(p.nOfOk() > 0)
        return 1;
}
