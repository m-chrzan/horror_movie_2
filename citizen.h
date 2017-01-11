#ifndef CITIZEN_H
#define CITIZEN_H

#include <cassert>
#include "helper.h"

class Citizen : public Character {
private:
	Age age_;

public:
	Citizen(HealthPoints health, Age age) : Character(health), age_(age) {}

    virtual ~Citizen() = 0;

	Age getAge() {
		return age_;
	}
};

inline Citizen::~Citizen() {}

class Teenager : public Citizen {
public:
	Teenager(HealthPoints health, Age age) : Citizen(health, age) {
		assert(age <= 17);
		assert(age >= 11);
	}
};

class Adult : public Citizen {
public:
	Adult(HealthPoints health, Age age) : Citizen(health, age) {
		assert(age >= 18);
		assert(age <= 100);
	}
};

class Sheriff : public Adult, public Attacker {
public:
	Sheriff(HealthPoints health, Age age, AttackPower power) :
            Adult(health, age), Attacker(power) {}
};

#endif
