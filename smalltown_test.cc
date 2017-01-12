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
    checkEqual<std::string>(status.getMonsterName(), "GroupOfMonsters",
            "Got the correct monster health.");
    checkEqual(status.getMonsterHealth(), 80.0, "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(), 3,
            "Got the right number of alive citizens.");
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
    checkEqual<std::string>(status.getMonsterName(), "GroupOfMonsters",
            "Got the correct monster name.");
    checkEqual(status.getMonsterHealth(), 60.0, "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(), 2,
            "Got the right number of alive citizens.");

    smallTown.tick(3);
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1, "A citizen died.");
}

void TestSmalltownBuilder() {
    beginTest();

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

    auto status = smallTown.getStatus();

    checkEqual<std::string>(status.getMonsterName(), "GroupOfMonsters",
            "Monster set correclty.");
    checkEqual(status.getMonsterHealth(), 140.0,
            "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(), 3,
            "Got the correct number of alive citizens.");

    smallTown.tick(18);
    smallTown.tick(3);

    status = smallTown.getStatus();
    checkEqual(status.getMonsterHealth(), 80.0,
            "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(),  3, "All citizens still alive.");
}

int main() {
    TestSmalltown();
    TestSmalltown2();
    TestSmalltownBuilder();
}
