#ifndef SMALLTOWN_H
#define SMALLTOWN_H

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

class SmallTown {
private:
    Time current_time_;
    Time max_time_;

    std::shared_ptr<Monster> monster_;
    std::vector<std::shared_ptr<Citizen>> citizens_;

    std::shared_ptr<Strategy> strategy_;

public:
    SmallTown(Time start_time, Time max_time, std::shared_ptr<Monster> monster,
              std::vector<std::shared_ptr<Citizen>> citizens,
              std::shared_ptr<Strategy> strategy) :
        current_time_(start_time), max_time_(max_time), monster_(monster),
        citizens_(citizens), strategy_(strategy) {}

    SmallTown(Time start_time, Time max_time, std::shared_ptr<Monster> monster,
              std::vector<std::shared_ptr<Citizen>> citizens) :
        SmallTown(start_time, max_time, monster, citizens, std::make_shared<DefaultStrategy>()) {}
};

#endif
