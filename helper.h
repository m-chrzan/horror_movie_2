#ifndef HELPER_H
#define HELPER_H

#include <cassert>
#include <algorithm>

using HealthPoints = double;
using Age = double;
using AttackPower = double;

class Character {
protected:
	HealthPoints health_;
	
	Character(HealthPoints health) : health_(health) {
		assert(health > 0);
	}
	
public:
	HealthPoints getHealth() {
		return health_;
	}
	
	virtual void takeDamage(AttackPower damage) {
		health_ -= std::min(health_, damage);
	}
};

class Attacker {
	
protected:
	AttackPower power_;
	Attacker(AttackPower power) : power_(power) {}
	
public:
	AttackPower getAttackPower() {
		return power_;
	}
};

#endif
