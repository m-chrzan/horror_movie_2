#ifndef HELPER_H
#define HELPER_H

using HealthPoints = double;
using Age = double;
using AttackPower = double;

class Character {
protected:
	HealthPoints hp;
	
	Character(HealthPoints hp) : hp(hp) {
		assert(hp > 0);
	}
	
public:
	HealthPoints getHealth() {
		return hp;
	}
	
	virtual void takeDamage(AttackPower damage) {
		hp = max(hp - damage, 0.0);
	}
};

class Attacker {
private:
	AttackPower ap;
	
protected:
	Attacker(AttackPower ap) : ap(ap) {}
	
public:
	AttackPower getAttackPower() {
		return ap;
	}
};

#endif
