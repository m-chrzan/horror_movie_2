#ifndef MONSTER_H
#define MONSTER_H

#include <memory>
#include <vector>
#include "helper.h"

class Monster : public Character, public Attacker {
protected:
	Monster(HealthPoints health, AttackPower power) : Character(health), Attacker(power) {}
};

class Mummy : public Monster {
public:
	Mummy(HealthPoints health, AttackPower power) : Monster(health, power) {}
};

class Vampire : public Monster {
public:
	Vampire(HealthPoints health, AttackPower power) : Monster(health, power) {}
};

class Zombie : public Monster {
public:
	Zombie(HealthPoints health, AttackPower power) : Monster(health, power) {}
};

HealthPoints addUpHealth(std::vector<std::shared_ptr<Monster>> &monsters) {
	HealthPoints sum = 0;
	for (auto monster : monsters) {
		sum += monster->getHealth();
	}
	return sum;
}

AttackPower addUpPower(std::vector<std::shared_ptr<Monster>> &monsters) {
	AttackPower sum = 0;
	for (auto monster : monsters) {
		sum += monster->getAttackPower();
	}
	return sum;
}

class GroupOfMonsters : public Monster {
private:
	std::vector<std::shared_ptr<Monster>> monsters_;
	
public:
	GroupOfMonsters(std::vector<std::shared_ptr<Monster>> monsters) 
		: Monster(addUpHealth(monsters), addUpPower(monsters)), monsters_(monsters) {}
	
	void takeDamage(AttackPower damage) {
		AttackPower powerSum = 0;
		HealthPoints healthSum = 0;
		for (auto monster : monsters_) {
			monster->takeDamage(damage);
			if (monster->getHealth() > 0) {
				powerSum += monster->getAttackPower();
				healthSum += monster->getHealth();
			}
		}
		power_ = powerSum;
		health_ = healthSum;
	}
};

std::shared_ptr<Mummy> createMummy(HealthPoints health, AttackPower power) {
	return std::make_shared<Mummy>(health, power);
}

std::shared_ptr<Vampire> createVampire(HealthPoints health, AttackPower power) {
	return std::make_shared<Vampire>(health, power);
}

std::shared_ptr<Zombie> createZombie(HealthPoints health, AttackPower power) {
	return std::make_shared<Zombie>(health, power);
}

std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::vector<std::shared_ptr<Monster>> monsters) {
	return std::make_shared<GroupOfMonsters>(monsters);
}


#endif
