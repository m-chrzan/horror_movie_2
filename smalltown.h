#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include <iostream>
#include <memory>
#include <set>
#include <vector>

#include "citizen.h"
#include "helper.h"
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
    unsigned aliveCitizens_;

public:
    Status(std::string const &name, HealthPoints health, int aliveCitizens) :
        monsterName_(name),
        monsterHealth_(health),
        aliveCitizens_(aliveCitizens) {}

    std::string getMonsterName() const {
        return monsterName_;
    }

    HealthPoints getMonsterHealth() const {
        return monsterHealth_;
    }

    unsigned getAliveCitizens() const {
        return aliveCitizens_;
    }
};

class SmallTownBuilder;

class SmallTown {
private:
    Time currentTime_;
    Time maxTime_;

    std::shared_ptr<Monster> monster_;
    std::vector<std::shared_ptr<Citizen>> citizens_;
    unsigned aliveCitizens_ = 0;
    std::shared_ptr<Strategy> strategy_;

    void doAttack_() {
        for (auto citizen : citizens_) {
            if (citizen->getHealth() > 0) {
                fight_(*monster_, *citizen);

                if (citizen->getHealth() == 0) {
                    aliveCitizens_--;
                }

                auto possibleAttacker = std::dynamic_pointer_cast<Attacker>(citizen);
                if (possibleAttacker) {
                    fight_(*possibleAttacker, *monster_);
                }
            }
        }
    }

    void fight_(Attacker &attacker, Character &victim) {
        victim.takeDamage(attacker.getAttackPower());
    }

    enum State { CITIZENS_WON, MONSTER_WON, DRAW, ONGOING };

    void announceState_() const {
        switch (getState_()) {
            case DRAW:
                std::cout << "DRAW" << std::endl;
                break;
            case CITIZENS_WON:
                std::cout << "CITIZENS WON" << std::endl;
                break;
            case MONSTER_WON:
                std::cout << "MONSTER WON" << std::endl;
                break;
            case ONGOING:
                break;
        }
    }

    State getState_() const {
        bool monsterDead = monster_->getHealth() == 0;
        bool citizensDead = aliveCitizens_ == 0;

        if (monsterDead && citizensDead) {
            return State::DRAW;
        } else if (monsterDead) {
            return State::CITIZENS_WON;
        } else if (citizensDead) {
            return State::MONSTER_WON;
        } else {
            return State::ONGOING;
        }
    }

public:
    using Builder = SmallTownBuilder;

    SmallTown(Time startTime, Time maxTime,
              std::shared_ptr<Monster> monster,
              std::vector<std::shared_ptr<Citizen>> citizens,
              std::shared_ptr<Strategy> strategy) :
        currentTime_(startTime),
        maxTime_(maxTime),
        monster_(monster),
        citizens_(citizens),
        aliveCitizens_(citizens.size()),
        strategy_(strategy) {}

    Status getStatus() const {
        return Status(monster_->getName(), monster_->getHealth(), aliveCitizens_);
    }

    void tick(Time timeStep) {
        if (strategy_->isAttackTime(currentTime_)) {
            doAttack_();
        }

        announceState_();

        currentTime_ = (currentTime_ + timeStep) % (maxTime_ + 1);
    }
};

class SmallTownBuilder {
private:
    std::vector<std::shared_ptr<Citizen>> citizens_;
    std::set<std::shared_ptr<Citizen>> citizensSet_;
    std::shared_ptr<Monster> monster_;
    bool startTimeSet_;
    bool maxTimeSet_;
    Time startTime_;
    Time maxTime_;
    std::shared_ptr<Strategy> strategy_;

    void checkReadyToBuild_() {
        if (!monster_) {
            throw std::logic_error("SmallTown needs a monster.");
        }

        if (citizensSet_.empty()) {
            throw std::logic_error("SmallTown needs at least one citizen.");
        }

        if (!startTimeSet_) {
            throw std::logic_error("SmallTown needs a start time.");
        }

        if (!maxTimeSet_) {
            throw std::logic_error("SmallTown needs a max time.");
        }

        if (startTime_ > maxTime_) {
            throw std::logic_error("Start time can't be larger than max time.");
        }
    }

public:
    SmallTownBuilder() : startTimeSet_(false),
                         maxTimeSet_(false),
                         strategy_(std::make_shared<DefaultStrategy>()) {}

    SmallTownBuilder &citizen(std::shared_ptr<Citizen> citizen) {
        if (citizensSet_.find(citizen) == citizensSet_.end()) {
            citizensSet_.insert(citizen);
            citizens_.push_back(citizen);
        }

        return *this;
    }

    SmallTownBuilder &monster(std::shared_ptr<Monster> monster) {
        monster_ = monster;

        return *this;
    }

    SmallTownBuilder &strategy(std::shared_ptr<Strategy> strategy) {
        strategy_ = strategy;

        return *this;
    }

    SmallTownBuilder &startTime(Time startTime) {
        startTime_ = startTime;
        startTimeSet_ = true;

        return *this;
    }

    SmallTownBuilder &maxTime(Time maxTime) {
        maxTime_ = maxTime;
        maxTimeSet_ = true;

        return *this;
    }

    SmallTown build() {
        checkReadyToBuild_();

        return SmallTown(startTime_, maxTime_, monster_, citizens_, strategy_);
    }
};

#endif
