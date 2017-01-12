#include "testing.h"
#include "monster.h"

void testZombieConstructor() {
    beginTest();

    Zombie zombie1(10U, 5U);
    checkEqual(zombie1.getHealth(), 10U, "Health set correctly.");
    checkEqual(zombie1.getAttackPower(), 5U, "Attack power set correctly.");

    Zombie zombie2(42U, 42U);
    checkEqual(zombie2.getHealth(), 42U, "Health set correctly.");
    checkEqual(zombie2.getAttackPower(), 42U, "Attack power set correctly.");
}

void testVampireConstructor() {
    beginTest();

    Vampire vampire1(10U, 5U);
    checkEqual(vampire1.getHealth(), 10U, "Health set correctly.");
    checkEqual(vampire1.getAttackPower(), 5U, "Attack power set correctly.");

    Vampire vampire2(42U, 42U);
    checkEqual(vampire2.getHealth(), 42U, "Health set correctly.");
    checkEqual(vampire2.getAttackPower(), 42U, "Attack power set correctly.");
}

void testMummyConstructor() {
    beginTest();

    Mummy mummy1(10U, 5U);
    checkEqual(mummy1.getHealth(), 10U, "Health set correctly.");
    checkEqual(mummy1.getAttackPower(), 5U, "Attack power set correctly.");

    Mummy mummy2(42U, 42U);
    checkEqual(mummy2.getHealth(), 42U, "Health set correctly.");
    checkEqual(mummy2.getAttackPower(), 42U, "Attack power set correctly.");
}

void testGroupOfMonstersConstructor() {
    beginTest();

    GroupOfMonsters group1{std::make_shared<Mummy>(23U, 11U),
                          std::make_shared<Vampire>(11U, 17U),
                          std::make_shared<Zombie>(8U, 14U)};

    checkEqual(group1.getHealth(), 42U, "Collective health set correctly.");
    checkEqual(group1.getAttackPower(), 42U,
            "Collective attack power set correctly.");

    GroupOfMonsters group2{std::make_shared<Mummy>(20U, 1U),
                           std::make_shared<Zombie>(15U, 2U),
                           std::make_shared<Vampire>(10U, 4U),
                           std::make_shared<Zombie>(5U, 8U)};

    checkEqual(group2.getHealth(), 50U, "Collective health set correctly.");
    checkEqual(group2.getAttackPower(), 15U,
            "Collective attack power set correctly.");
}

void testZombieTakeDamage() {
    beginTest();

    Zombie zombie1(20U, 1U);

    zombie1.takeDamage(1U);
    checkEqual(zombie1.getHealth(), 19U, "Took damage.");
    checkEqual(zombie1.getAttackPower(), 1U, "Attack power unchanged.");

    zombie1.takeDamage(19U);
    checkEqual(zombie1.getHealth(), 0U, "Took damage.");

    zombie1.takeDamage(42U);
    checkEqual(zombie1.getHealth(), 0U, "No damage taken when at 0.");

    Zombie zombie2(100U, 13U);
    zombie2.takeDamage(989123U);
    checkEqual(zombie2.getHealth(), 0U, "Damage doesn't go below 0.");
}

void testVampireTakeDamage() {
    beginTest();

    Vampire vampire1(20U, 1U);

    vampire1.takeDamage(1U);
    checkEqual(vampire1.getHealth(), 19U, "Took damage.");
    checkEqual(vampire1.getAttackPower(), 1U, "Attack power unchanged.");

    vampire1.takeDamage(19U);
    checkEqual(vampire1.getHealth(), 0U, "Took damage.");

    vampire1.takeDamage(42U);
    checkEqual(vampire1.getHealth(), 0U, "No damage taken when at 0.");

    Vampire vampire2(100U, 13U);
    vampire2.takeDamage(989123U);
    checkEqual(vampire2.getHealth(), 0U, "Damage doesn't go below 0.");
}

void testMummyTakeDamage() {
    beginTest();

    Mummy mummy1(20U, 1U);

    mummy1.takeDamage(1U);
    checkEqual(mummy1.getHealth(), 19U, "Took damage.");
    checkEqual(mummy1.getAttackPower(), 1U, "Attack power unchanged.");

    mummy1.takeDamage(19U);
    checkEqual(mummy1.getHealth(), 0U, "Took damage.");

    mummy1.takeDamage(42U);
    checkEqual(mummy1.getHealth(), 0U, "No damage taken when at 0.");

    Mummy mummy2(100U, 13U);
    mummy2.takeDamage(989123U);
    checkEqual(mummy2.getHealth(), 0U, "Damage doesn't go below 0.");
}

void testGroupOfMonstersTakeDamage() {
    beginTest();

    GroupOfMonsters group1{std::make_shared<Mummy>(20U, 1U),
                           std::make_shared<Zombie>(15U, 2U),
                           std::make_shared<Vampire>(10U, 4U),
                           std::make_shared<Zombie>(5U, 8U)};

    group1.takeDamage(1U);
    checkEqual(group1.getHealth(), 46U, "Each monster's health reduced.");
    checkEqual(group1.getAttackPower(), 15U, "Attack power not reduced.");

    group1.takeDamage(4U);
    checkEqual(group1.getHealth(), 30U, "Each monster's health reduced.");
    checkEqual(group1.getAttackPower(), 7U,
            "Attack power reduced after monster death.");

    group1.takeDamage(5U);
    checkEqual(group1.getHealth(), 15U,
            "Only living monsters' health reduced.");
    checkEqual(group1.getAttackPower(), 3U, "Another monster died.");

    group1.takeDamage(10U);
    checkEqual(group1.getHealth(), 0U, "Rest of monster's killed.");
    checkEqual(group1.getAttackPower(), 0U, "Attack power reduced to 0.");
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
