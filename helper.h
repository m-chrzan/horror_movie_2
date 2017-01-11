#ifndef HELPER_H
#define HELPER_H

#include <cassert>
#include <algorithm>

using HealthPoints = double;
using Age = double;
using AttackPower = double;

class Character {
private:
	HealthPoints health_;

public:
	Character(HealthPoints health) : health_(health) {
		assert(health_ > 0);
	}

    virtual ~Character() = 0;

	HealthPoints getHealth() {
		return health_;
	}

	virtual void takeDamage(AttackPower damage) {
        if (damage > health_) {
            health_ = 0;
        } else {
            health_ -= damage;
        }
	}
};

inline Character::~Character() {}

class Attacker {
private:
	AttackPower power_;

public:
	Attacker(AttackPower power) : power_(power) {}

    virtual ~Attacker() = 0;
	AttackPower getAttackPower() {
		return power_;
	}
};

inline Attacker::~Attacker() {}

#endif
