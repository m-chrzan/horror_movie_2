#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include "testing.h"

void TestSmalltown() {
    beginTest();
    
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });
    auto smallTown = SmallTown(3, 27, groupOfMonsters,
        std::vector<std::shared_ptr<Citizen>>{
        createSheriff(100, 35, 20),
        createAdult(100, 21),
        createTeenager(50, 14)}, std::make_shared<DefaultStrategy>());
    smallTown.tick(1);
    
    smallTown.tick(18);
    smallTown.tick(3);
    
    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 80);
    assert(status.getAliveCitizens() == 3);
    checkEqual(1, 1, "Status OK");
}

void TestSmalltown2() {
    beginTest();
    
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 40),
        createZombie(20, 1),
        createVampire(30, 1)
    });
    
    auto smallTown = SmallTown(3, 40, groupOfMonsters,
        std::vector<std::shared_ptr<Citizen>>{
        createSheriff(100, 35, 30),
        createAdult(80, 21),
        createTeenager(40, 14)}, std::make_shared<DefaultStrategy>());
    
    smallTown.tick(3);
    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 60);
    assert(status.getAliveCitizens() == 2);
    
    smallTown.tick(3);
    status = smallTown.getStatus();
    assert(status.getAliveCitizens() == 1);
    
    checkEqual(1, 1, "Status OK");
}

void TestSmalltownBuilder() {
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });
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
}

int main() {
    TestSmalltown();
    TestSmalltown2();
    TestSmalltownBuilder();
}
