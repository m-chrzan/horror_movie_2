#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include "helper.h"
#include "citizen.h"
#include "monster.h"

using Time = unsigned;

class Strategy {
public:
    virtual bool isAttackTime(Time time) const = 0;
};

class DefaultStrategy : public Strategy {
public:
    bool isAttackTime(Time time) const {
        bool divisibleBy3 = (time % 3) == 0;
        bool divisibleBy13 = (time % 13) == 0;
        bool divisibleBy7 = (time % 7) == 0;

        return (divisibleBy3 || divisibleBy13) && !divisibleBy7;
    }
};

class Status {
private:
    std::string monsterName_;
    HealthPoints monsterHealth_;
    int aliveCitizens_;
    
public:
    Status(std::string const &name, HealthPoints health, int aliveCits) :
        monsterName_(name), monsterHealth_(health), aliveCitizens_(aliveCits) {}

    std::string getMonsterName() const {
        return monsterName_;
    }

    HealthPoints getMonsterHealth() const {
        return monsterHealth_;
    }

    int getAliveCitizens() const {
        return aliveCitizens_;
    }
};

class SmallTown {
private:
    Time current_time_;
    Time max_time_;

    std::shared_ptr<Monster> monster_;
    std::vector<std::shared_ptr<Citizen>> citizens_;
    int aliveCitizens_ = 0;
    std::shared_ptr<Strategy> strategy_;

public:
    SmallTown(Time start_time, Time max_time, std::shared_ptr<Monster> monster,
              std::vector<std::shared_ptr<Citizen>> citizens,
              std::shared_ptr<Strategy> strategy) :
        current_time_(start_time), max_time_(max_time), monster_(monster),
        citizens_(citizens), aliveCitizens_(citizens.size()), strategy_(strategy) {}

    SmallTown(Time start_time, Time max_time, std::shared_ptr<Monster> monster,
              std::vector<std::shared_ptr<Citizen>> citizens) :
        SmallTown(start_time, max_time, monster, citizens, 
                  std::make_shared<DefaultStrategy>()) {}

    Status getStatus() const {
        return Status(monster_->getName(), monster_->getHealth(), aliveCitizens_);
    }

    void tick(Time timeStep) {
        if (strategy_->isAttackTime(current_time_)) {
            for (auto citizen : citizens_) {
                if (citizen->getHealth() > 0) {
                    citizen->takeDamage(monster_->getAttackPower());
                    if (citizen->getHealth() == 0) {
                        aliveCitizens_--;
                    }
                    auto possibleSheriff = dynamic_cast<Sheriff*>(citizen.get());
                    if (possibleSheriff != nullptr) {
                        monster_->takeDamage(possibleSheriff->getAttackPower());
                    }
                }
            }
        }
        current_time_ = (current_time_ + timeStep) % (max_time_ + 1);
    }
};

#endif
