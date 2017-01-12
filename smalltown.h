#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include <set>
#include <vector>

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

class SmallTownBuilder;

class SmallTown {
private:
    Time currentTime_;
    Time maxTime_;

    std::shared_ptr<Monster> monster_;
    std::vector<std::shared_ptr<Citizen>> citizens_;

    std::shared_ptr<Strategy> strategy_;

public:
    using Builder = SmallTownBuilder;
    SmallTown(Time startTime, Time maxTime, std::shared_ptr<Monster> monster,
              std::vector<std::shared_ptr<Citizen>> citizens,
              std::shared_ptr<Strategy> strategy) :
        currentTime_(startTime), maxTime_(maxTime), monster_(monster),
        citizens_(citizens), strategy_(strategy) {}
};

class SmallTownBuilder {
private:
    std::vector<std::shared_ptr<Citizen>> citizens_;
    std::set<std::shared_ptr<Citizen>> citizensSet_;
    std::shared_ptr<Monster> monster_;
    Time startTime_;
    Time maxTime_;
    std::shared_ptr<Strategy> strategy_;

    void checkReadyToBuild_() {
        if (monster_.get() == nullptr) {
            throw std::logic_error("SmallTown needs a monster.");
        }

        if (citizensSet_.empty()) {
            throw std::logic_error("SmallTown needs at least one citizen.");
        }

        if (startTime_ > maxTime_) {
            throw std::logic_error("Start time can't be larger than max time.");
        }
    }

public:
    SmallTownBuilder() : strategy_(std::make_shared<DefaultStrategy>()) {}
    SmallTownBuilder & citizen(std::shared_ptr<Citizen> citizen) {
        if (citizensSet_.find(citizen) != citizensSet_.end()) {
            citizensSet_.insert(citizen);
            citizens_.push_back(citizen);
        }

        return *this;
    }

    SmallTownBuilder & monster(std::shared_ptr<Monster> monster) {
        monster_ = monster;

        return *this;
    }

    SmallTownBuilder & strategy(std::shared_ptr<Strategy> strategy) {
        strategy_ = strategy;

        return *this;
    }

    SmallTownBuilder & startTime(Time startTime) {
        startTime_ = startTime;

        return *this;
    }

    SmallTownBuilder & maxTime(Time maxTime) {
        maxTime_ = maxTime;

        return *this;
    }

    SmallTown build() {
        checkReadyToBuild_();

        return SmallTown(startTime_, maxTime_, monster_, citizens_, strategy_);
    }
};

#endif
