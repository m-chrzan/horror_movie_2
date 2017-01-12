#ifndef CITIZEN_H
#define CITIZEN_H

#include <cassert>
#include <memory>

#include "helper.h"

class Citizen : public Character {
private:
    Age age_;

public:
    Citizen(HealthPoints health, Age age) : Character(health), age_(age) {}

    virtual ~Citizen() = 0;

    Age getAge() const {
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

std::shared_ptr<Teenager> createTeenager(HealthPoints health, Age age) {
    return std::make_shared<Teenager>(health, age);
}

std::shared_ptr<Adult> createAdult(HealthPoints health, Age age) {
    return std::make_shared<Adult>(health, age);
}

std::shared_ptr<Sheriff> createSheriff(HealthPoints health, Age age, AttackPower power) {
    return std::make_shared<Sheriff>(health, age, power);
}

#endif
