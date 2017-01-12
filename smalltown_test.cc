#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include "testing.h"

void testSmallTown() {
    beginTest();

    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90U, 1U),
        createZombie(20U, 1U),
        createVampire(30U, 1U)
    });
    auto smallTown = SmallTown(3U, 27U, groupOfMonsters,
        std::vector<std::shared_ptr<Citizen>>{
        createSheriff(100U, 35U, 20U),
        createAdult(100U, 21U),
        createTeenager(50U, 14U)}, std::make_shared<DefaultStrategy>());
    smallTown.tick(1U);

    smallTown.tick(18U);
    smallTown.tick(3U);

    auto status = smallTown.getStatus();
    checkEqual<std::string>(status.getMonsterName(), "GroupOfMonsters",
            "Got the correct monster health.");
    checkEqual(status.getMonsterHealth(), 80U, "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(), 3U,
            "Got the right number of alive citizens.");
}

void testSmallTown2() {
    beginTest();

    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90U, 40U),
        createZombie(20U, 1U),
        createVampire(30U, 1U)
    });

    auto smallTown = SmallTown(3U, 40U, groupOfMonsters,
        std::vector<std::shared_ptr<Citizen>>{
        createSheriff(100U, 35U, 30U),
        createAdult(80U, 21U),
        createTeenager(40U, 14U)}, std::make_shared<DefaultStrategy>());

    smallTown.tick(3U);
    auto status = smallTown.getStatus();
    checkEqual<std::string>(status.getMonsterName(), "GroupOfMonsters",
            "Got the correct monster name.");
    checkEqual(status.getMonsterHealth(), 60U, "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(), 2U,
            "Got the right number of alive citizens.");

    smallTown.tick(3U);
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1U, "A citizen died.");
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

    auto zombie = createZombie(13U, 23U);
    auto teen = createTeenager(23U, 13U);
    Time start = 0U;
    Time max = 7U;

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

    startGreaterThanMax.citizen(teen).maxTime(10U).monster(zombie).startTime(12U);

}

void testSmallTownBuilder() {
    beginTest();

    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90U, 1U),
        createZombie(20U, 1U),
        createVampire(30U, 1U)
    });

    auto sheriff = createSheriff(100U, 35U, 20U);

    auto smallTown = SmallTown::Builder()
        .monster(groupOfMonsters)
        .startTime(3U)
        .maxTime(27U)
        .citizen(sheriff)
        .citizen(sheriff) // second instance of same sheriff should be ignored
        .citizen(createAdult(100U, 21U))
        .citizen(createTeenager(50U, 14U))
        .build();

    auto status = smallTown.getStatus();

    checkEqual<std::string>(status.getMonsterName(), "GroupOfMonsters",
            "Monster set correclty.");
    checkEqual(status.getMonsterHealth(), 140U,
            "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(), 3U,
            "Got the correct number of alive citizens.");

    smallTown.tick(18U);
    smallTown.tick(3U);

    status = smallTown.getStatus();
    checkEqual(status.getMonsterHealth(), 80U,
            "Got the correct monster health.");
    checkEqual(status.getAliveCitizens(),  3U, "All citizens still alive.");
}

void testSmallTownDefaultStrategy() {
    beginTest();
    
    auto monster = createMummy(90U, 1U);
    
    auto smallTown = SmallTown::Builder()
        .monster(monster)
        .startTime(0U)
        .maxTime(27U)
        .citizen(createAdult(1U, 21U))
        .citizen(createAdult(2U, 21U))
        .citizen(createAdult(3U, 21U))
        .citizen(createAdult(4U, 21U))
        .citizen(createAdult(5U, 21U))
        .build();
        
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 5U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(3U); //0U->3U no attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 5U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(10U); //3U->13U attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 4U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(8U); //13U->21U attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 3U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(6U); //21U-27U no attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 3U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(1U); //27U->0U attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 2U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(26U); //0U->26U no attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 2U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(1U); //26U->27U attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1U,
               "Got the correct number of alive citizens.");
    
    smallTown.tick(1U); //27U->0U attack
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 0U,
               "All citizens dead.");

}

void testSmallTownDraw() {
    beginTest();
    
    auto monster = createMummy(90U, 1U);
    
    auto smallTown = SmallTown::Builder()
    .monster(monster)
    .startTime(13U)
    .maxTime(27U)
    .citizen(createSheriff(1U, 21U, 90U))
    .build();
    
    smallTown.tick(1U);
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 0U,
               "All citizens dead.");
    checkEqual(status.getMonsterHealth(), 0U,
               "Monster dead.");
    
    smallTown.tick(100U);
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 0U,
               "All citizens dead.");
    checkEqual(status.getMonsterHealth(), 0U,
               "Monster dead.");
}

void testSmallTownCitizensWon() {
    beginTest();
    
    auto monster = createMummy(90U, 1U);
    
    auto smallTown = SmallTown::Builder()
    .monster(monster)
    .startTime(13U)
    .maxTime(27U)
    .citizen(createAdult(1U, 21U))
    .citizen(createSheriff(2U, 21U, 90U))
    .citizen(createAdult(1U, 21U))
    .build();
    
    smallTown.tick(3U);
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 2U,
               "Sheriff alive.");
    checkEqual(status.getMonsterHealth(), 0U,
               "Monster dead.");
    
    smallTown.tick(100U);
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 2U,
               "Sheriff still alive.");
    checkEqual(status.getMonsterHealth(), 0U,
               "Monster still dead.");
}

void testSmallTownOrderOfAttacking() {
    beginTest();
    
    auto monster = createMummy(90U, 1U);
    
    auto smallTown = SmallTown::Builder()
    .monster(monster)
    .startTime(13U)
    .maxTime(27U)
    .citizen(createAdult(1U, 21U))
    .citizen(createSheriff(1U, 21U, 90U))
    .citizen(createAdult(1U, 21U))
    .build();
    
    smallTown.tick(3U);
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1U,
               "Monster died before killing everyone.");
}

void testSmallTownOrderOfAttackingGroup() {
    beginTest();
    
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(60U, 1U),
        createZombie(20U, 1U),
        createVampire(30U, 1U)
    });
    
    auto smallTown = SmallTown::Builder()
    .monster(groupOfMonsters)
    .startTime(3U)
    .maxTime(27U)
    .citizen(createAdult(1U, 21U))
    .citizen(createSheriff(4U, 99U, 30U))
    .citizen(createAdult(2U, 21U))
    .build();
    
    smallTown.tick(3U);
    auto status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 2U,
               "Group of monsters killed a person.");
    checkEqual(status.getMonsterHealth(), 30U,
               "2 of the monsters died.");
    
    smallTown.tick(3U);
    status = smallTown.getStatus();
    checkEqual(status.getAliveCitizens(), 1U,
               "One person survived thanks to Sheriff.");
    checkEqual(status.getMonsterHealth(), 0U,
               "Last monster died.");
}

int main() {
    testSmallTown();
    testSmallTown2();
    testSmallTownIncorrectBuilder();
    testSmallTownBuilder();
    testSmallTownDefaultStrategy();
    testSmallTownDraw();
    testSmallTownCitizensWon();
    testSmallTownOrderOfAttacking();
    testSmallTownOrderOfAttackingGroup();
}
