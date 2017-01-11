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

int main() {
    testTeenagerConstructor();
    testAdultConstructor();
    testSheriffConstructor();
}
