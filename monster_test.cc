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

void testZombieTakeDamage() {
    beginTest();

    Zombie zombie1(20.0, 1.0);

    zombie1.takeDamage(1.0);
    checkEqual(zombie1.getHealth(), 19.0, "Took damage.");
    checkEqual(zombie1.getAttackPower(), 1.0, "Attack power unchanged.");

    zombie1.takeDamage(19.0);
    checkEqual(zombie1.getHealth(), 0.0, "Took damage.");

    zombie1.takeDamage(42.0);
    checkEqual(zombie1.getHealth(), 0.0, "No damage taken when at 0.");

    Zombie zombie2(100.0, 13.0);
    zombie2.takeDamage(989123.0);
    checkEqual(zombie2.getHealth(), 0.0, "Damage doesn't go below 0.");
}

void testVampireTakeDamage() {
    beginTest();

    Vampire vampire1(20.0, 1.0);

    vampire1.takeDamage(1.0);
    checkEqual(vampire1.getHealth(), 19.0, "Took damage.");
    checkEqual(vampire1.getAttackPower(), 1.0, "Attack power unchanged.");

    vampire1.takeDamage(19.0);
    checkEqual(vampire1.getHealth(), 0.0, "Took damage.");

    vampire1.takeDamage(42.0);
    checkEqual(vampire1.getHealth(), 0.0, "No damage taken when at 0.");

    Vampire vampire2(100.0, 13.0);
    vampire2.takeDamage(989123.0);
    checkEqual(vampire2.getHealth(), 0.0, "Damage doesn't go below 0.");
}

void testMummyTakeDamage() {
    beginTest();

    Mummy mummy1(20.0, 1.0);

    mummy1.takeDamage(1.0);
    checkEqual(mummy1.getHealth(), 19.0, "Took damage.");
    checkEqual(mummy1.getAttackPower(), 1.0, "Attack power unchanged.");

    mummy1.takeDamage(19.0);
    checkEqual(mummy1.getHealth(), 0.0, "Took damage.");

    mummy1.takeDamage(42.0);
    checkEqual(mummy1.getHealth(), 0.0, "No damage taken when at 0.");

    Mummy mummy2(100.0, 13.0);
    mummy2.takeDamage(989123.0);
    checkEqual(mummy2.getHealth(), 0.0, "Damage doesn't go below 0.");
}

void testGroupOfMonstersTakeDamage() {
    beginTest();

    GroupOfMonsters group1{std::make_shared<Mummy>(20.0, 1.0),
                           std::make_shared<Zombie>(15.0, 2.0),
                           std::make_shared<Vampire>(10.0, 4.0),
                           std::make_shared<Zombie>(5.0, 8.0)};

    group1.takeDamage(1.0);
    checkEqual(group1.getHealth(), 46.0, "Each monster's health reduced.");
    checkEqual(group1.getAttackPower(), 15.0, "Attack power not reduced.");

    group1.takeDamage(4.0);
    checkEqual(group1.getHealth(), 30.0, "Each monster's health reduced.");
    checkEqual(group1.getAttackPower(), 7.0,
            "Attack power reduced after monster death.");

    group1.takeDamage(5.0);
    checkEqual(group1.getHealth(), 15.0,
            "Only living monsters' health reduced.");
    checkEqual(group1.getAttackPower(), 3.0, "Another monster died.");

    group1.takeDamage(10.0);
    checkEqual(group1.getHealth(), 0.0, "Rest of monster's killed.");
    checkEqual(group1.getAttackPower(), 0.0, "Attack power reduced to 0.");
}

int main() {
    testZombieConstructor();
    testVampireConstructor();
    testMummyConstructor();
    testGroupOfMonstersConstructor();

    testZombieTakeDamage();
    testVampireTakeDamage();
    testMummyTakeDamage();
    testGroupOfMonstersTakeDamage();
}
