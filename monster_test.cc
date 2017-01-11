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

void testGroupOfMonstersConstructor() {
    beginTest();

    GroupOfMonsters group1{std::make_shared<Mummy>(23.0, 11.0),
                          std::make_shared<Vampire>(11.0, 17.0),
                          std::make_shared<Zombie>(8.0, 14.0)};

    checkEqual(group1.getHealth(), 42.0, "Collective health set correctly.");
    checkEqual(group1.getAttackPower(), 42.0,
            "Collective attack power set correctly.");

    GroupOfMonsters group2{std::make_shared<Mummy>(20.0, 1.0),
                           std::make_shared<Zombie>(15.0, 2.0),
                           std::make_shared<Vampire>(10.0, 4.0),
                           std::make_shared<Zombie>(5.0, 8.0)};

    checkEqual(group2.getHealth(), 50.0, "Collective health set correctly.");
    checkEqual(group2.getAttackPower(), 15.0,
            "Collective attack power set correctly.");
}

int main() {
    testZombieConstructor();
    testVampireConstructor();
    testMummyConstructor();
    testGroupOfMonstersConstructor();
}
