//
//  horror_example.cc
//  horror-movie-2
//
//  Created by Patrycja Wegrzynowicz on 12/10/16.
//  Copyright (c) 2016 Patrycja Wegrzynowicz. All rights reserved.
//

#include "citizen.h"
#include "monster.h"
#include "smalltown.h"

#include <iostream>
#include <cassert>
using namespace std;

int main(int argc, const char * argv[]) {
	
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });
	
	assert(groupOfMonsters->getHealth() == 140);
	assert(groupOfMonsters->getAttackPower() == 3);
	
	groupOfMonsters->takeDamage(30);
	assert(groupOfMonsters->getHealth() == 60);
	assert(groupOfMonsters->getAttackPower() == 1);
	
	groupOfMonsters->takeDamage(60);
	assert(groupOfMonsters->getHealth() == 0);
	assert(groupOfMonsters->getAttackPower() == 0);
	
	auto groupOfMonsters2 = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });
	shared_ptr<Monster> gom = (shared_ptr<Monster>) groupOfMonsters2;
	
	assert(gom->getHealth() == 140);
	assert(gom->getAttackPower() == 3);
	
	gom->takeDamage(30);
	assert(gom->getHealth() == 60);
	assert(gom->getAttackPower() == 1);
	/*
    auto smallTown = SmallTown::Builder()
        .monster(groupOfMonsters)
        .startTime(3)
        .maxTime(27)
        .citizen(createSheriff(100, 35, 20))
        .citizen(createAdult(100, 21))
        .citizen(createTeenager(50, 14))
        .build();

    smallTown.tick(18);
    smallTown.tick(3);

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 80);
    assert(status.getAliveCitizens() == 3);

    return 0;*/
}
