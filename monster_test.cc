#include "testing.h"
#include "monster.h"

void testZombieConstructor() {
    beginTest();

    Zombie zombie1(10.0, 5.0);
    checkEqual(zombie1.getHealth(), 10.0, "Health set correctly.");
    checkEqual(zombie1.getAttackPower(), 5.0, "Attack power set correctly.");

    Zombie zombie2(42.0, 42.0);
    checkEqual(zombie2.getHealth(), 42.0, "Health set correctly.");
    checkEqual(zombie2.getAttackPower(), 42.0, "Attack power set correctly.");
}

void testVampireConstructor() {
    beginTest();

    Vampire vampire1(10.0, 5.0);
    checkEqual(vampire1.getHealth(), 10.0, "Health set correctly.");
    checkEqual(vampire1.getAttackPower(), 5.0, "Attack power set correctly.");

    Vampire vampire2(42.0, 42.0);
    checkEqual(vampire2.getHealth(), 42.0, "Health set correctly.");
    checkEqual(vampire2.getAttackPower(), 42.0, "Attack power set correctly.");
}

void testMummyConstructor() {
    beginTest();

    Mummy mummy1(10.0, 5.0);
    checkEqual(mummy1.getHealth(), 10.0, "Health set correctly.");
    checkEqual(mummy1.getAttackPower(), 5.0, "Attack power set correctly.");

    Mummy mummy2(42.0, 42.0);
    checkEqual(mummy2.getHealth(), 42.0, "Health set correctly.");
    checkEqual(mummy2.getAttackPower(), 42.0, "Attack power set correctly.");
}


int main() {
    testZombieConstructor();
    testVampireConstructor();
    testMummyConstructor();
}
