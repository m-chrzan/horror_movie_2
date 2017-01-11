#ifndef CITIZEN_H
#define CITIZEN_H

#include "helper.h"

class Citizen : public Character {
protected:
	Age age;
	
	Citizen(HealthPoints hp, Age age) : Character(hp), age(age) {}
	
public:
	Age getAge() {
		return age;
	}
};

class Teen : public Citizen {
public:
	Teen(HealthPoints hp, Age age) : Citizen(hp, age) {
		assert(age <= 17);
		assert(age >= 11);
	}
};

class Adult : public Citizen {
public:
	Adult(HealthPoints hp, Age age) : Citizen(hp, age) {
		assert(age >= 18);
		assert(age <= 100);
	}
};

class Sheriff : public Adult, public Attacker {
public:
	Sheriff(HealthPoints hp, Age age, AttackPower ap) : Adult(hp, age), Attacker(ap) {}
};

#endif
