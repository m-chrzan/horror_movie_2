#include "citizen.h"
#include "testing.h"

void testTeenagerConstructor() {
    beginTest();

    Teenager teen1(10.0, 15.0);
    checkEqual(teen1.getHealth(), 10.0, "Health set correctly.");
    checkEqual(teen1.getAge(), 15.0, "Age set correctly.");

    Teenager teen2(42.0, 11.0);
    checkEqual(teen2.getHealth(), 42.0, "Health set correctly.");
    checkEqual(teen2.getAge(), 11.0, "Age set correctly.");
}

void testAdultConstructor() {
    beginTest();

    Adult adult1(10.0, 18.0);
    checkEqual(adult1.getHealth(), 10.0, "Health set correctly.");
    checkEqual(adult1.getAge(), 18.0, "Age set correctly.");

    Adult adult2(42.0, 42.0);
    checkEqual(adult2.getHealth(), 42.0, "Health set correctly.");
    checkEqual(adult2.getAge(), 42.0, "Age set correctly.");
}

void testSheriffConstructor() {
    beginTest();

    Sheriff sheriff1(10.0, 18.0, 5.0);
    checkEqual(sheriff1.getHealth(), 10.0, "Health set correctly.");
    checkEqual(sheriff1.getAge(), 18.0, "Age set correctly.");
    checkEqual(sheriff1.getAttackPower(), 5.0, "Attack power set correctly.");

    Sheriff sheriff2(42.0, 42.0, 42.0);
    checkEqual(sheriff2.getHealth(), 42.0, "Health set correctly.");
    checkEqual(sheriff2.getAge(), 42.0, "Age set correctly.");
    checkEqual(sheriff2.getAttackPower(), 42.0, "Attack power set correctly.");
}

void testTeenagerTakeDamage() {
    beginTest();

    Teenager teenager1(20.0, 11.0);

    teenager1.takeDamage(1.0);
    checkEqual(teenager1.getHealth(), 19.0, "Took damage.");

    teenager1.takeDamage(19.0);
    checkEqual(teenager1.getHealth(), 0.0, "Took damage.");

    teenager1.takeDamage(42.0);
    checkEqual(teenager1.getHealth(), 0.0, "No damage taken when at 0.");

    Teenager teenager2(100.0, 13.0);
    teenager2.takeDamage(989123.0);
    checkEqual(teenager2.getHealth(), 0.0, "Damage doesn't go below 0.");
}

void testAdultTakeDamage() {
    beginTest();

    Adult adult1(20.0, 21.0);

    adult1.takeDamage(1.0);
    checkEqual(adult1.getHealth(), 19.0, "Took damage.");

    adult1.takeDamage(19.0);
    checkEqual(adult1.getHealth(), 0.0, "Took damage.");

    adult1.takeDamage(42.0);
    checkEqual(adult1.getHealth(), 0.0, "No damage taken when at 0.");

    Adult adult2(100.0, 99.0);
    adult2.takeDamage(989123.0);
    checkEqual(adult2.getHealth(), 0.0, "Damage doesn't go below 0.");
}

void testSheriffTakeDamage() {
    beginTest();

    Sheriff sheriff1(20.0, 21.0, 1.0);

    sheriff1.takeDamage(1.0);
    checkEqual(sheriff1.getHealth(), 19.0, "Took damage.");
    checkEqual(sheriff1.getAttackPower(), 1.0, "Attack power unchanged.");

    sheriff1.takeDamage(19.0);
    checkEqual(sheriff1.getHealth(), 0.0, "Took damage.");

    sheriff1.takeDamage(42.0);
    checkEqual(sheriff1.getHealth(), 0.0, "No damage taken when at 0.");

    Sheriff sheriff2(100.0, 99.0, 20000.0);
    sheriff2.takeDamage(989123.0);
    checkEqual(sheriff2.getHealth(), 0.0, "Damage doesn't go below 0.");
}

int main() {
    testTeenagerConstructor();
    testAdultConstructor();
    testSheriffConstructor();

    testTeenagerTakeDamage();
    testAdultTakeDamage();
    testSheriffTakeDamage();
}
