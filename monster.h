#ifndef MONSTER_H
#define MONSTER_H

#include "helper.h"

class Monster : public Character, public Attacker {
protected:
	Monster(HealthPoints health, AttackPower power) : Character(health), Attacker(power) {}
}

class Mummy : public Monster {
public:
	Mummy(HealthPoints health, AttackPower power) : Monster(health, power) {}
}

class Vampire : public Monster {
public:
	Vampire(HealthPoints health, AttackPower power) : Monster(health, power) {}
}

class Zombie : public Monster {
public:
	Zombie(HealthPoints health, AttackPower power) : Monster(health, power) {}
}

HealthPoints addHealth(std::vector<shared_ptr<Monster>> &monsters) {
	
}

class GroupOfMonsters : public Monster {
private:
	std::vector<shared_ptr<Monster>> monsters_;
	
public:
	GroupOfMonsters(std::vector<shared_ptr<Monster>> monsters) : Monster(addHealth(monsters), addPower(monsters)), monsters_(monsters) {}
}

#endif
