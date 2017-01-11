#include "citizen.h"
#include "testing.h"

void testTeenagerConstructor() {
    beginTest();

    Teenager teen1(10, 15);
    checkEqual(teen1.getHealth(), 10, "Health set correctly.");
    checkEqual(teen1.getAge(), 15, "Age set correctly.");

    Teenager teen2(42, 11);
    checkEqual(teen2.getHealth(), 42, "Health set correctly.");
    checkEqual(teen2.getAge(), 11, "Age set correctly.");
}

void testAdultConstructor() {
    beginTest();

    Adult adult1(10, 18);
    checkEqual(adult1.getHealth(), 10, "Health set correctly.");
    checkEqual(adult1.getAge(), 18, "Age set correctly.");

    Adult adult2(42, 42);
    checkEqual(adult2.getHealth(), 42, "Health set correctly.");
    checkEqual(adult2.getAge(), 42, "Age set correctly.");
}

void testSheriffConstructor() {
    beginTest();

    Sheriff sheriff1(10, 18, 5);
    checkEqual(sheriff1.getHealth(), 10, "Health set correctly.");
    checkEqual(sheriff1.getAge(), 18, "Age set correctly.");
    checkEqual(sheriff1.getAttackPower(), 5, "Attack power set correctly.");

    Sheriff sheriff2(42, 42, 42);
    checkEqual(sheriff2.getHealth(), 42, "Health set correctly.");
    checkEqual(sheriff2.getAge(), 42, "Age set correctly.");
    checkEqual(sheriff2.getAttackPower(), 42, "Attack power set correctly.");
}

int main() {
    testTeenagerConstructor();
    testAdultConstructor();
    testSheriffConstructor();
}
