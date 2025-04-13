#include "pch.h"
#include "globals.h"
#include "functions.h"

uintptr_t baseAddress = 0;


uint8_t currentChapter = 0;

const uintptr_t activeChapterOffset = 0x222EEC8;

uintptr_t activeChapterAddress = 0;

uintptr_t returnInjectTripleIS = 0;

uintptr_t returnInjectDelimb1 = 0;

uintptr_t returnInjectDelimb2 = 0;

uintptr_t returnInjectDelimb3 = 0;

uintptr_t returnInjectAnim = 0;

uintptr_t returnInjectHalfCut = 0;

uintptr_t returnInjectFreeCam = 0;

uintptr_t returnInjectFreeCamCall = 0x10521B4;

uintptr_t returnInjectInventoryCCNew;

uintptr_t returnInjectSound = 0;

uintptr_t returnInjectC = 0;

uintptr_t returnInjectFOV = 0;

uintptr_t returnInjectDelimbFiends = 0;

uintptr_t returnInjectCoords = 0;

uintptr_t returnInjectCLoop = 0;

uintptr_t returnInjectEventTrigger = 0;

uintptr_t returnInjectDisableSpawns = 0;

uintptr_t returnInjectEntDie = 0;

uintptr_t returnInjectHalfCutHuman = 0;

uintptr_t returnEnemyDmgReduction = 0;

uintptr_t returnInjectEntHitData = 0;

uintptr_t returnInjectAIDodge = 0;

uintptr_t returnInjectRecoveryPunish = 0;

uintptr_t RecoveryPunishLeaOffset = 0x215FA80;

uintptr_t RecoveryPunishLeaAddress = 0;

uintptr_t returnInjectIDrop = 0;

uintptr_t returnInjectUTCharge = 0;

uintptr_t returnInjectInput = 0;

uintptr_t returnInjectLockCam = 0;

uintptr_t returnInjectCamShake = 0;

uintptr_t returnInjectChargeUltimate = 0;

uintptr_t injectChargeUltimateJE = 0x10053C2;

uintptr_t injectChargeUltimateCall = 0x10054B0;

uintptr_t returnInjectWepDmg;

unsigned char tripleISBytes[] = {
        0x00, 0x00, 0x01, 0x00, 0x44, 0x00, 0x00, 0x00, 0x0E, 0x00, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x09, 0x00, 0x00, 0x00, 0x18, 0x00,
        0x0E, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x00, 0x00, 0x00, 0x0E, 0x00,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x24, 0x00, 0x08, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x44, 0x00, 0x00, 0x00, 0x0E, 0x00, 0xFF, 0xFF, 0x00, 0x00,
        0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


float resistance = 0.75f;
float detectTest = 1.70f;
float detectTest2 = 75.0f;
float newVal1 = 1.0f;
float newVal2 = 100.0f;
float newVal3 = 1.20f;
float newVal4 = 1.20f;
float teleCoords = 0.00f;
float telePlayer = 0.00f;
float resistancemax = -1.00f;
float guilthrowDmgMulp = 1.50f;
float scytheDelimbMulp = 1.50f;
float enmaDelimbMulp = 1.50f;
float femaleDelimbMulp = 1.50f;
float highDelimbMulp = 1.80f;
float masterEnemyDMGMulp = 1.70f;
float mentorEnemyDMGMulp = 1.20f;
float warriorEnemyDMGMulp = 1.00f;
float masterEnemyDmgReductionMulp = 2.00f;
float mentorEnemyDmgReductionMulp = 1.00f;
float warriorEnemyDmgReductionMulp = 1.00f;
float fsDelimbMulp = 1.50;
float bowChargeDelimbMulp = 5.00f;
float bowETDmgMulp = 1.50f;
float bowUTDmgMulp = 3.50f;

//CHANGED TO INCLUDE MENTOR AND WARRIOR
DWORD_PTR masterEnemyHPMulpAddress[] = {
     0x1EAAD80, // MASTER
     0x1EAAD74, // MENTOR
     0x1EAAD68 // WARRIOR
   //HP MULP 0x1EAAD80
    //MELEE DAMAGE 0x1EAAD84
    // GRAB DAMAGE 0x1EAAD88
   /* 0x1EAAD40, 0x1EAAD44, 0x1EAAD48, 0x1EAAD4C,
    0x1EAAD88, 0x1EAADC4, 0x1EAAE04, 0x1EAAE08,
    0x1EAAE48, 0x1EAAE54, 0x1EAAE60, 0x1EAAE64,
    0x1EAAE68, 0x1EAAE7C, 0x1EAAE88, 0x1EAAE90,
    0x1EAAE94, 0x1EAAEA0, 0x1EAAEA4, 0x1EAAEA8,
    0x1EAAEC0, 0x1EAAF00, 0x1EAAF20, 0x1EAAF24,
    0x1EAAF28, 0x1EAAF64, 0x1EAAF68,0x1EAAEE4,
    0x1EAAEE8,0x1EAAD84,0x1EAADC8*/
};

size_t masterEnemyHPMulpAddressSize = 1;//sizeof(masterEnemyHPMulpAddress) / sizeof(masterEnemyHPMulpAddress[0]);

uintptr_t microStutterOffset01 = 0x1529E35;
uintptr_t microStutterOffset02 = 0x1529E3F;


bool isNinjaGrabSpeed = false;
bool greyNinjaGrabSpeed = false;
bool zedGrabSpeed = false;
bool lizGrabSpeedTail = true;
bool tripleIS = true;
bool vangelfGrabSpeed = false;

BYTE microStutter = 0x00;
bool storyHPCC = true;

bool isFreeCamAll = false;
bool isFreeCamIzunaOnly = true;
bool cameraHitImpact = true;

bool inventoryCCNew;

uint8_t cBattleRespawnCount = 0;
uint8_t cBattleRespawnCount2 = 0;
uint8_t cBattleRespawnCount3 = 0;
uint8_t cBattleRespawnCount4 = 0;
uint8_t cBattleRespawnCount5 = 0;
uint8_t cBattleRespawnCount6 = 0;
uint8_t cBattleRespawnCount7 = 0;
uint8_t cBattleRespawnCount8 = 0;
uint8_t cBattleRespawnCount9 = 0;
uint8_t cManualSpawnResetCounter = 0;


BYTE mainMenuTrack = 0x52;
BYTE ch1HeroTrack = 0x3D;
BYTE ch14HeroTrack = 0x4D;

float fovValue = 0.13f;
float defaultFOV = 0.87f;

const uint16_t lycanHalfCutTable[] = {
    0x049A, //DS
    0x049E, //BOTA 0E
    0x04A2, //CLAWS 0B
    0x04A6, //SCYTHE
};

const uint16_t fsMoveTable[] = {
    0x0C7A, 
    0x0C7C, 
    0x0D6E, 
    0x0CA8,
    0x0D66, 
    0x07BB 
};



uint8_t canSpawn = 0;
uint8_t canspawn2 = 0;
uint8_t diffInjected = 0;

uintptr_t activeDiffOffset = 0x36265C8;

uintptr_t pHpAddress;
const uintptr_t pHpOffset = 0x3380DB6;

const uintptr_t enemyAliveOffset = 0x2FB74A8; //0x2FC59AC;
const uintptr_t enemyAliveOffset2 = 0x2233104;
uintptr_t enemyAliveAddress = 0;
uintptr_t enemyAliveAddress2 = 0;



uint8_t cDeleteEnemy = 0;

int randomNum = 0;
uint16_t entDied;

bool freezeEnemies = false;


bool ch1RasetsuDisableMinions = false;
bool ch2RasetsuDisableMinions = false;
bool ch14RasForDoppler = false;

uintptr_t entHitAddress = 0;
uintptr_t entHitID = 0;
uint8_t isNinjaDodgeBlockChance = 40;
uint8_t isFiendNinjaDodgeBlockChance = 100;
uint8_t lizDodgeBlockChance = 100;
uint8_t brownNinjaDodgeBlockChance = 40;

EntHitInfo entHitInfo;

uintptr_t playerIdentOffset1 = 0x33754F0;
uintptr_t playerIdentAddress1 = 0;

bool izunaRecoveryPunish = true;

const uint16_t izunaAnimIDs[] = { 0x0E39, 0x0E3A, 0x0D84, 0x0D5D };
const size_t izunaAnimIDsSize = sizeof(izunaAnimIDs) / sizeof(izunaAnimIDs)[0];

const uint16_t iDropTable[] = { 0x09A7, 0x07FE, 0x077D, 0x0876 };
const size_t iDropTableSize = sizeof(iDropTable) / sizeof(iDropTable)[0];

const uintptr_t pAnimOffset = 0x3380E30;
extern "C" uintptr_t pAnimAddress = 0;

float etChargeTime = 50.00;
float utChargeTime = 110.00;

uintptr_t playerSurfaceTypeOffset = 0x3380F03;
uintptr_t playerSurfaceTypeAddress = 0;

uint32_t userInput = 0x00000000;

uintptr_t lockcamAdd1 = 0x222EE90;
uintptr_t lockcamAdd2 = 0x2FD2150;
uintptr_t lockcamAdd3 = 0x222EEC4;

uint8_t canWaterDragonAttacks = 0;
bool canWaterDragonOT = false;
uint8_t waterDragonBattleStart = false;
bool waterDragonDived = false;
bool canSwapCoords = false;


uintptr_t openMuramasaShopOffset = 0x215C7A2;
uintptr_t openMuramasaShopAddress = 0;

bool canChargeCustomUltimate = false;
bool skipTask = false;