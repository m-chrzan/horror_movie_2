#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include "testing.h"

void testSmallTown() {
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

void testSmallTown2() {
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

void testSmallTownIncorrectBuilder() {
    beginTest();

    SmallTown::Builder empty;

    checkExceptionThrown<std::logic_error>([&empty] {
        auto smallTown = empty.build();
    }, "Can't build unitialized smalltown.");

    SmallTown::Builder noMonster;
    SmallTown::Builder noCitizen;
    SmallTown::Builder noStartTime;
    SmallTown::Builder noMaxTime;

    auto zombie = createZombie(13, 23);
    auto teen = createTeenager(23, 13);
    Time start = 0;
    Time max = 7;

    noMonster.citizen(teen).maxTime(max).startTime(start);
    noCitizen.maxTime(max).monster(zombie).startTime(start);
    noStartTime.citizen(teen).maxTime(max).monster(zombie);
    noMaxTime.citizen(teen).monster(zombie).startTime(start);

    checkExceptionThrown<std::logic_error>([&noMonster] {
        auto smallTown = noMonster.build();
    }, "Can't build a town without a monster.");

    checkExceptionThrown<std::logic_error>([&noCitizen] {
        auto smallTown = noCitizen.build();
    }, "Can't build a town without a citizen.");

    checkExceptionThrown<std::logic_error>([&noStartTime] {
        auto smallTown = noStartTime.build();
    }, "Can't build a town without a start time.");

    checkExceptionThrown<std::logic_error>([&noMaxTime] {
        auto smallTown = noMaxTime.build();
    }, "Can't build a town without an max time.");

    SmallTown::Builder startGreaterThanMax;

    startGreaterThanMax.citizen(teen).maxTime(10).monster(zombie).startTime(12);

}

void testSmallTownBuilder() {
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

void testSmallTownDefaultStrategy() {
    beginTest();
    
    auto monster = createMummy(90, 1);
    
    auto smallTown = SmallTown::Builder()
        .monster(monster)
        .startTime(0)
        .maxTime(27)
        .citizen(createAdult(1, 21))
        .citizen(createAdult(2, 21))
        .citizen(createAdult(3, 21))
        .citizen(createAdult(4, 21))
        .citizen(createAdult(5, 21))
        .build();
        
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 5,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(3); //0->3 no attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 5,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(10); //3->13 attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 4,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(8); //13->21 attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 3,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(6); //21-27 no attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 3,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(1); //27->0 attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 2,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(26); //0->26 no attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 2,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(1); //26->27 attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(1); //27->0 attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 0,
               "All citizens dead.");

}

void testSmallTownDraw() {
    beginTest();
    
    auto monster = createMummy(90, 1);
    
    auto smallTown = SmallTown::Builder()
    .monster(monster)
    .startTime(13)
    .maxTime(27)
    .citizen(createSheriff(1, 21, 90))
    .build();
    
    smallTown.tick(1);
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 0,
               "All citizens dead.");
    checkEqual(status.getMonsterHealth(), 0.0, 
               "Monster dead.");
    
    smallTown.tick(100);
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 0,
               "All citizens dead.");
    checkEqual(status.getMonsterHealth(), 0.0, 
               "Monster dead.");
}

void testSmallTownCitizensWon() {
    beginTest();
    
    auto monster = createMummy(90, 1);
    
    auto smallTown = SmallTown::Builder()
    .monster(monster)
    .startTime(13)
    .maxTime(27)
    .citizen(createSheriff(2, 21, 90))
    .citizen(createAdult(1, 21))
    .build();
    
    smallTown.tick(3);
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1,
               "Sheriff alive.");
    checkEqual(status.getMonsterHealth(), 0.0, 
               "Monster dead.");
    
    smallTown.tick(100);
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1,
               "Sheriff still alive.");
    checkEqual(status.getMonsterHealth(), 0.0, 
               "Monster still dead.");
}

int main() {
    testSmallTown();
    testSmallTown2();
    testSmallTownIncorrectBuilder();
    testSmallTownBuilder();
    testSmallTownDefaultStrategy();
    testSmallTownDraw();
    testSmallTownCitizensWon();
}
