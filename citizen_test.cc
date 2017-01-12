#include "citizen.h"
#include "testing.h"

void testTeenagerConstructor() {
    beginTest();

    Teenager teen1(10U, 15U);
    checkEqual(teen1.getHealth(), 10U, "Health set correctly.");
    checkEqual(teen1.getAge(), 15U, "Age set correctly.");

    Teenager teen2(42U, 11U);
    checkEqual(teen2.getHealth(), 42U, "Health set correctly.");
    checkEqual(teen2.getAge(), 11U, "Age set correctly.");
}

void testAdultConstructor() {
    beginTest();

    Adult adult1(10U, 18U);
    checkEqual(adult1.getHealth(), 10U, "Health set correctly.");
    checkEqual(adult1.getAge(), 18U, "Age set correctly.");

    Adult adult2(42U, 42U);
    checkEqual(adult2.getHealth(), 42U, "Health set correctly.");
    checkEqual(adult2.getAge(), 42U, "Age set correctly.");
}

void testSheriffConstructor() {
    beginTest();

    Sheriff sheriff1(10U, 18U, 5U);
    checkEqual(sheriff1.getHealth(), 10U, "Health set correctly.");
    checkEqual(sheriff1.getAge(), 18U, "Age set correctly.");
    checkEqual(sheriff1.getAttackPower(), 5U, "Attack power set correctly.");

    Sheriff sheriff2(42U, 42U, 42U);
    checkEqual(sheriff2.getHealth(), 42U, "Health set correctly.");
    checkEqual(sheriff2.getAge(), 42U, "Age set correctly.");
    checkEqual(sheriff2.getAttackPower(), 42U, "Attack power set correctly.");
}

void testTeenagerTakeDamage() {
    beginTest();

    Teenager teenager1U(20U, 11U);

    teenager1U.takeDamage(1U);
    checkEqual(teenager1U.getHealth(), 19U, "Took damage.");

    teenager1U.takeDamage(19U);
    checkEqual(teenager1U.getHealth(), 0U, "Took damage.");

    teenager1U.takeDamage(42U);
    checkEqual(teenager1U.getHealth(), 0U, "No damage taken when at 0.");

    Teenager teenager2U(100U, 13U);
    teenager2U.takeDamage(989123U);
    checkEqual(teenager2U.getHealth(), 0U, "Damage doesn't go below 0.");
}

void testAdultTakeDamage() {
    beginTest();

    Adult adult1(20U, 21U);

    adult1.takeDamage(1U);
    checkEqual(adult1.getHealth(), 19U, "Took damage.");

    adult1.takeDamage(19U);
    checkEqual(adult1.getHealth(), 0U, "Took damage.");

    adult1.takeDamage(42U);
    checkEqual(adult1.getHealth(), 0U, "No damage taken when at 0.");

    Adult adult2(100U, 99U);
    adult2.takeDamage(989123U);
    checkEqual(adult2.getHealth(), 0U, "Damage doesn't go below 0.");
}

void testSheriffTakeDamage() {
    beginTest();

    Sheriff sheriff1(20U, 21U, 1U);

    sheriff1.takeDamage(1U);
    checkEqual(sheriff1.getHealth(), 19U, "Took damage.");
    checkEqual(sheriff1.getAttackPower(), 1U, "Attack power unchanged.");

    sheriff1.takeDamage(19U);
    checkEqual(sheriff1.getHealth(), 0U, "Took damage.");

    sheriff1.takeDamage(42U);
    checkEqual(sheriff1.getHealth(), 0U, "No damage taken when at 0.");

    Sheriff sheriff2(100U, 99U, 20000U);
    sheriff2.takeDamage(989123U);
    checkEqual(sheriff2.getHealth(), 0U, "Damage doesn't go below 0.");
}

int main() {
    testTeenagerConstructor();
    testAdultConstructor();
    testSheriffConstructor();

    testTeenagerTakeDamage();
    testAdultTakeDamage();
    testSheriffTakeDamage();
}
