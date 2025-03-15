#pragma once
#include <cstdint>
#include <Windows.h>
//RYU ANIM OFFSET: 337D550 / NEW 3380E30
//RYU WEAPON EQUIPPED OFFSET: 337D506 / NEW 3380DE6
//RYU PROJECTILE OFFSET: 337D508 / NEW 3380DE8
//RYU HP: 337D4D6 / NEW 3380DB6
//RYU CERTAIN STATES (I.E 04 = on water) 3380F03

extern "C" uintptr_t baseAddress;

extern "C" uintptr_t returnInjectTripleIS;

extern "C" uintptr_t returnInjectDelimb1;

extern "C" uintptr_t returnInjectDelimb2;

extern "C" uintptr_t returnInjectDelimb3;

extern "C" uintptr_t returnInjectAnim;

extern "C" uintptr_t returnInjectHalfCut;

extern "C" uintptr_t returnInjectFreeCam;

extern "C" uintptr_t returnInjectFreeCamCall;

extern "C" uintptr_t returnInjectInventoryCCNew;

extern "C" uintptr_t returnInjectSound;

extern "C" uintptr_t returnInjectC;

extern "C" uintptr_t returnInjectFOV;

extern "C" uintptr_t returnInjectDelimbFiends;

extern "C" uintptr_t returnInjectCLoop;

extern "C" uintptr_t returnInjectCoords;

extern "C" uintptr_t returnInjectEventTrigger;

extern "C" uintptr_t returnInjectDisableSpawns;

extern "C" uintptr_t returnInjectEntDie;

extern "C" uintptr_t returnInjectHalfCutHuman;

extern "C" uintptr_t returnEnemyDmgReduction;

extern "C" uintptr_t returnInjectEntHitData;

extern "C" uintptr_t returnInjectAIDodge;

extern "C" uintptr_t returnInjectRecoveryPunish;

extern "C" uintptr_t RecoveryPunishLeaOffset;

extern "C" uintptr_t RecoveryPunishLeaAddress;

extern "C" uintptr_t returnInjectIDrop;

extern "C" uintptr_t returnInjectUTCharge;

extern "C" uintptr_t returnInjectInput;

extern "C" uintptr_t returnInjectLockCam;

extern "C" uintptr_t returnInjectCamShake;

extern "C" unsigned char tripleISBytes[];

//DELIMB 
extern "C" float resistance;
extern "C" float detectTest;
extern "C" float detectTest2;
extern "C" float newVal1;
extern "C" float newVal2;
extern "C" float newVal3;
extern "C" float newVal4;
extern "C" float teleCoords;
extern "C" float telePlayer;
extern "C" float resistancemax;
extern "C" float guilthrowDmgMulp;
extern "C" float scytheDelimbMulp;
extern "C" float enmaDelimbMulp;
extern "C" float femaleDelimbMulp;
extern "C" float highDelimbMulp;
extern float masterEnemyDMGMulp;
extern DWORD_PTR masterEnemyHPMulpAddress[];
extern size_t masterEnemyHPMulpAddressSize;
extern "C" float masterEnemyDmgReductionMulp;
extern "C" float mentorEnemyDmgReductionMulp;
extern "C" float warriorEnemyDmgReductionMulp;
extern "C" float fsDelimbMulp;

//HITSTOP
extern uintptr_t microStutterOffset01;
extern uintptr_t microStutterOffset02;

//ENEMY AI
extern "C" bool isNinjaGrabSpeed;
extern "C" bool greyNinjaGrabSpeed;
extern "C" bool zedGrabSpeed;
extern "C" bool lizGrabSpeedTail;
extern "C" bool tripleIS;
extern "C" bool vangelfGrabSpeed;

//GAMEPLAY
extern BYTE microStutter;
extern bool storyHPCC;

//CAMERA
extern "C" bool isFreeCamAll;
extern "C" bool isFreeCamIzunaOnly;
extern "C" bool cameraHitImpact;

extern "C" bool inventoryCCNew;

//SPAWN COUNTERS
extern "C" uint8_t cBattleRespawnCount;
extern "C" uint8_t cBattleRespawnCount2;
extern "C" uint8_t cBattleRespawnCount3;
extern "C" uint8_t cBattleRespawnCount4;
extern "C" uint8_t cBattleRespawnCount5;
extern "C" uint8_t cBattleRespawnCount6;
extern "C" uint8_t cBattleRespawnCount7;
extern "C" uint8_t cBattleRespawnCount8;
extern "C" uint8_t cBattleRespawnCount9;
extern "C" uint8_t cManualSpawnResetCounter;

//AUDIO
extern "C" BYTE mainMenuTrack;
extern "C" BYTE ch1HeroTrack;
extern "C" BYTE ch14HeroTrack;

//CAMERA
extern "C" float fovValue;
extern "C" float defaultFOV;

extern "C" const uint16_t lycanHalfCutTable[];
extern "C" const uint16_t fsMoveTable[];

//INJECT C
extern "C" uint8_t canSpawn;
extern "C" uint8_t canspawn2;

//DEBUG
extern bool freezeEnemies;


//DIFFICULTY RELATED
extern uint8_t diffInjected;
extern const uintptr_t activeChapterOffset;
extern "C" uintptr_t activeChapterAddress;

extern "C" uintptr_t activeDiffOffset;
extern "C" uint8_t currentChapter;

extern "C" const uintptr_t pHpOffset;
extern "C" uintptr_t pHpAddress;

extern "C" const uintptr_t pAnimOffset;
extern "C" uintptr_t pAnimAddress;


extern const uintptr_t enemyAliveOffset;
extern const uintptr_t enemyAliveOffset2;
extern "C" uintptr_t enemyAliveAddress;
extern "C" uintptr_t enemyAliveAddress2;
extern "C" uint8_t cDeleteEnemy;

//RAND
extern "C" int randomNum;
extern "C" uint16_t entDied;

//SPAWN
extern "C" bool ch1RasetsuDisableMinions;
extern "C" bool ch2RasetsuDisableMinions;
extern "C" bool ch14RasForDoppler;

//AIDODGE
extern "C" uintptr_t entHitAddress;
extern "C" uintptr_t entHitID;
extern "C" uint8_t isNinjaDodgeBlockChance;
extern "C" uint8_t isFiendNinjaDodgeBlockChance;
extern "C" uint8_t lizDodgeBlockChance;

struct EntHitInfo
{
	uintptr_t address;
	uint16_t ID;
	uint8_t Playerstate;
};

extern "C" EntHitInfo entHitInfo;

//PLAYER IDENT
extern "C" uintptr_t playerIdentOffset1;
extern "C" uintptr_t playerIdentAddress1;

//ENEMY AI
extern "C" bool izunaRecoveryPunish;

extern "C" const uint16_t izunaAnimIDs[];
extern "C" const size_t izunaAnimIDsSize;

extern "C" const uint16_t iDropTable[];
extern "C" const size_t iDropTableSize;

//GAMEPLAY
extern "C" float etChargeTime;
extern "C" float utChargeTime;

extern "C" uintptr_t playerSurfaceTypeOffset;
extern "C" uintptr_t playerSurfaceTypeAddress;

extern "C" uint32_t userInput;

//LOCK UNLOCK BOSS CAM
extern "C" uintptr_t lockcamAdd1;
extern "C" uintptr_t lockcamAdd2;
extern "C" uintptr_t lockcamAdd3;

//WATER DRAGON
extern "C" uint8_t canWaterDragonAttacks;
extern "C" bool canWaterDragonOT;
extern "C" uint8_t waterDragonBattleStart;
extern "C" bool waterDragonDived;

extern "C" bool canSwapCoords;