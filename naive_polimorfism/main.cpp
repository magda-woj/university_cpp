#include <iostream>
#include "Character.h"
#include "Item.h"
#include "Weapon.h"
#include "MagicWeapon.h"
#include "Medicine.h"
void weaken(Character& c){
    c.setDefense(c.getDefense()-2);
}
int main() {
    Character Alice(5);
    Weapon* sword = new Weapon(18);
    Alice.addItem(sword);
    Character Bob;
    Alice.use(0, Bob);
    MagicWeapon* magicSword = new MagicWeapon(18, weaken);
    Bob.addItem(magicSword);
    Bob.use(0, Alice);
    Medicine* med = new Medicine(10);
    Alice.addItem(med);
    Alice.use(1,Alice);
    return 0;
}
