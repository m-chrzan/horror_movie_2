#ifndef MONSTER_H
#define MONSTER_H

#include <initializer_list>
#include <memory>
#include <vector>

#include "helper.h"

class Monster : public Character, public Attacker {
protected:
    Monster(HealthPoints health, AttackPower power) : 
        Character(health), Attacker(power) {}

public:
    virtual std::string getName() const = 0;
};

class Mummy : public Monster {
public:
    Mummy(HealthPoints health, AttackPower power) : Monster(health, power) {}

    std::string getName() const {
        return "Mummy";
    }
};

class Vampire : public Monster {
public:
    Vampire(HealthPoints health, AttackPower power) : Monster(health, power) {}

    std::string getName() const {
        return "Vampire";
    }
};

class Zombie : public Monster {
public:
    Zombie(HealthPoints health, AttackPower power) : Monster(health, power) {}

    std::string getName() const {
        return "Zombie";
    }
};


class GroupOfMonsters : public Monster {
private:
    std::vector<std::shared_ptr<Monster>> monsters_;

    static HealthPoints addUpHealth(std::vector<std::shared_ptr<Monster>> const &monsters) {
        HealthPoints sum = 0;
        for (auto monster : monsters) {
            sum += monster->getHealth();
        }

        return sum;
    }

    static HealthPoints addUpHealth(std::initializer_list<std::shared_ptr<Monster>> const &monsters) {
        HealthPoints sum = 0;
        for (auto monster : monsters) {
            sum += monster->getHealth();
        }

        return sum;
    }

    static AttackPower addUpPower(std::vector<std::shared_ptr<Monster>> &monsters) {
        AttackPower sum = 0;
        for (auto monster : monsters) {
            sum += monster->getAttackPower();
        }

        return sum;
    }

    static AttackPower addUpPower(std::initializer_list<std::shared_ptr<Monster>> const &monsters) {
        AttackPower sum = 0;
        for (auto monster : monsters) {
            sum += monster->getAttackPower();
        }

        return sum;
    }

public:
    GroupOfMonsters(std::vector<std::shared_ptr<Monster>> monsters) :
        Monster(addUpHealth(monsters), addUpPower(monsters)),
        monsters_(monsters) {}

    GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster>> monsters) :
        Monster(addUpHealth(monsters), addUpPower(monsters)),
        monsters_(monsters) {}

    std::string getName() const {
        return "GroupOfMonsters";
    }

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
