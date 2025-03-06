#pragma once
#include <cstdint>
#include <Windows.h>


struct BattleCoords;
struct SpawnCoords;
struct BattleTracker;
struct DistanceThreshold;


#pragma region MENTOR_MASTER
extern "C" BattleCoords masterninjabtlCH1BattleCoords[];
extern "C" BattleTracker masterninjabtlCH1Tracker[];
extern "C" DistanceThreshold masterninjabtlCH1DistanceThreshold[];
extern "C" SpawnCoords masterninjabtlCH1SpawnCoords[];
extern "C" uintptr_t masterninjaCH1OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords masterninjabtlCH2BattleCoords[];
extern "C" BattleTracker masterninjabtlCH2Tracker[];
extern "C" DistanceThreshold masterninjabtlCH2DistanceThreshold[];
extern "C" SpawnCoords masterninjabtlCH2SpawnCoords[];
extern "C" uintptr_t masterninjaCH2OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords masterninjabtlCH3BattleCoords[];
extern "C" BattleTracker masterninjabtlCH3Tracker[];
extern "C" DistanceThreshold masterninjabtlCH3DistanceThreshold[];
extern "C" SpawnCoords masterninjabtlCH3SpawnCoords[];
extern "C" uintptr_t masterninjaCH3OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords masterninjabtlCH4BattleCoords[];
extern "C" BattleTracker masterninjabtlCH4Tracker[];
extern "C" DistanceThreshold masterninjabtlCH4DistanceThreshold[];
extern "C" SpawnCoords masterninjabtlCH4SpawnCoords[];
extern "C" uintptr_t masterninjaCH4OriginalSpawnTriggerOffsets[];

extern "C" const uint16_t chp4MuesumSpawn[];
extern "C" const size_t chp4MuesumSpawnSize;
extern "C" uint8_t chp4MuesumBtlCounter;
extern "C" const uint8_t chp4MuesumBtlMaxSpawnCap;

extern "C" const uint16_t chp4MuesumSpawnMentor[];
extern "C" const size_t chp4MuesumSpawnSizeMentor;
extern "C" uint8_t chp4MuesumBtlCounterMentor;
extern "C" const uint8_t chp4MuesumBtlMaxSpawnCapMentor;

extern "C" const uint16_t chp4MuesumSpawnWarrior[];
extern "C" const size_t chp4MuesumSpawnSizeWarrior;
extern "C" uint8_t chp4MuesumBtlCounterWarrior;
extern "C" const uint8_t chp4MuesumBtlMaxSpawnCapWarrior;

extern "C" const uint16_t chp6RebirthSpawn[];
extern "C" const size_t chp6RebirthSpawnSize;
extern "C" uint8_t chp6RebirthBtlCounter;
extern "C" const uint8_t chp6RebirthBtlMaxSpawnCap;

extern "C" const uint16_t chp6SecondSaveAmbushSpawn[];
extern "C" uint8_t chp6SecondSaveBtlCounter;
extern "C" const size_t chp6SecondSaveAmbushSpawnSize;

extern "C" const uint16_t chp6RebirthSpawnMentor[];
extern "C" const size_t chp6RebirthSpawnSizeMentor;
extern "C" uint8_t chp6RebirthBtlCounterMentor;
extern "C" const uint8_t chp6RebirthBtlMaxSpawnCapMentor;

extern "C" const uint16_t chp6SecondSaveAmbushSpawnMentor[];
extern "C" uint8_t chp6SecondSaveBtlCounterMentor;
extern "C" const size_t chp6SecondSaveAmbushSpawnSizeMentor;





extern "C" BattleCoords masterninjabtlCH6BattleCoords[];
extern "C" BattleTracker masterninjabtlCH6Tracker[];
extern "C" DistanceThreshold masterninjabtlCH6DistanceThreshold[];
extern "C" SpawnCoords masterninjabtlCH6SpawnCoords[];
extern "C" uintptr_t masterninjaCH6OriginalSpawnTriggerOffsets[];


extern "C" uintptr_t masterninjaCH7OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords masterninjabtlCH10BattleCoords[];
extern "C" BattleTracker masterninjabtlCH10Tracker[];
extern "C" DistanceThreshold masterninjabtlCH10DistanceThreshold[];
extern "C" SpawnCoords masterninjabtlCH10SpawnCoords[];
extern "C" uintptr_t masterninjaCH10OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords masterninjabtlCH14BattleCoords[];
extern "C" BattleTracker masterninjabtlCH14Tracker[];
extern "C" DistanceThreshold masterninjabtlCH14DistanceThreshold[];
extern "C" SpawnCoords masterninjabtlCH14SpawnCoords[];
extern "C" uintptr_t masterninjaCH14OriginalSpawnTriggerOffsets[];




extern const size_t masterninjabtlCH1TrackerSize;
extern const size_t masterninjabtlCH2TrackerSize;
extern const size_t masterninjabtlCH3TrackerSize;
extern const size_t masterninjabtlCH4TrackerSize;
extern const size_t masterninjabtlCH6TrackerSize;
extern const size_t masterninjabtlCH10TrackerSize;
extern const size_t masterninjabtlCH14TrackerSize;


extern unsigned int* masterMasterBattleTrackers[];
extern size_t masterMasterBattleTrackersSize[];


extern const size_t masterMasterBattleTrackersCount;
#pragma endregion

#pragma region WARRIOR

extern "C" BattleCoords warriorbtlCH1BattleCoords[];
extern "C" BattleTracker warriorbtlCH1Tracker[];
extern "C" DistanceThreshold warriorbtlCH1DistanceThreshold[];
extern "C" SpawnCoords warriorbtlCH1SpawnCoords[];
extern "C" uintptr_t warriorCH1OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords warriorbtlCH2BattleCoords[];
extern "C" BattleTracker warriorbtlCH2Tracker[];
extern "C" DistanceThreshold warriorbtlCH2DistanceThreshold[];
extern "C" SpawnCoords warriorbtlCH2SpawnCoords[];
extern "C" uintptr_t warriorCH2OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords warriorbtlCH3BattleCoords[];
extern "C" BattleTracker warriorbtlCH3Tracker[];
extern "C" DistanceThreshold warriorbtlCH3DistanceThreshold[];
extern "C" SpawnCoords warriorbtlCH3SpawnCoords[];
extern "C" uintptr_t warriorCH3OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords warriorbtlCH4BattleCoords[];
extern "C" BattleTracker warriorbtlCH4Tracker[];
extern "C" DistanceThreshold warriorbtlCH4DistanceThreshold[];
extern "C" SpawnCoords warriorbtlCH4SpawnCoords[];
extern "C" uintptr_t warriorCH4OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords warriorbtlCH6BattleCoords[];
extern "C" BattleTracker warriorbtlCH6Tracker[];
extern "C" DistanceThreshold warriorbtlCH6DistanceThreshold[];
extern "C" SpawnCoords warriorbtlCH6SpawnCoords[];
extern "C" uintptr_t warriorCH6OriginalSpawnTriggerOffsets[];

extern "C" const uint16_t chp6RebirthSpawnWarrior[];
extern "C" const size_t chp6RebirthSpawnSizeWarrior;
extern "C" uint8_t chp6RebirthBtlCounterWarrior;
extern "C" const uint8_t chp6RebirthBtlMaxSpawnCapWarrior;

extern "C" const uint16_t chp6SecondSaveAmbushSpawnWarrior[];
extern "C" uint8_t chp6SecondSaveBtlCounterWarrior;
extern "C" const size_t chp6SecondSaveAmbushSpawnSizeWarrior;

extern "C" BattleCoords warriorbtlCH10BattleCoords[];
extern "C" BattleTracker warriorbtlCH10Tracker[];
extern "C" DistanceThreshold warriorbtlCH10DistanceThreshold[];
extern "C" SpawnCoords warriorbtlCH10SpawnCoords[];
extern "C" uintptr_t warriorCH10OriginalSpawnTriggerOffsets[];

extern "C" BattleCoords warriorbtlCH14BattleCoords[];
extern "C" BattleTracker warriorbtlCH14Tracker[];
extern "C" DistanceThreshold warriorbtlCH14DistanceThreshold[];
extern "C" SpawnCoords warriorbtlCH14SpawnCoords[];
extern "C" uintptr_t warriorCH14OriginalSpawnTriggerOffsets[];




extern const size_t warriorbtlCH1TrackerSize;
extern const size_t warriorbtlCH2TrackerSize;
extern const size_t warriorbtlCH3TrackerSize;
extern const size_t warriorbtlCH4TrackerSize;
extern const size_t warriorbtlCH10TrackerSize;
extern const size_t warriorbtlCH14TrackerSize;

extern unsigned int* warriorWarriorBattleTrackers[];
extern size_t warriorWarriorBattleTrackersSize[];

extern const size_t warriorWarriorBattleTrackersCount;


#pragma endregion