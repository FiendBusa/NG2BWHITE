#include "pch.h"
#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <fstream>
#include <iostream>
#include <iomanip>
#include "globals.h"
#include "hook.h"
#include "functions.h"
#include "SimpleIni.h"
#include "spawndata.h"
#include <random>
#include <chrono>
#include "mentor.h"
#include "warrior.h"


//#include "bass.h"

//#pragma comment(lib,"bass.lib")

/*Author: Fiend Busa*/



DWORD_PTR GetBaseAddress(LPCWSTR module) {
    return (DWORD_PTR)GetModuleHandle(module);
}


struct HookInfo {
    DWORD_PTR offset;
    int length;
    void* hookFunction;
    const char* hookName;
    DWORD_PTR* returnAddress;
    int nopeLen;
};

void NopMemory(void* address, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memset(address, 0x90, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}




TCHAR* GetExecutablePath(TCHAR* exePath, DWORD size) {
    GetModuleFileName(NULL, exePath, size);
    TCHAR* lastSlash = wcsrchr(exePath, '\\');
    if (lastSlash) {
        *lastSlash = '\0';
    }
    return exePath;
}

void LoadConfig() {
    TCHAR exePath[MAX_PATH];
    GetExecutablePath(exePath, MAX_PATH);


    std::wstring iniPath = std::wstring(exePath) + L"\\mods\\bin\\NG2BWHITE\\config.ini";

    CSimpleIniW ini;
    ini.SetUnicode();

    SI_Error rc = ini.LoadFile(iniPath.c_str());
    if (rc < 0) {
        MessageBox(NULL, L"Can't load 'config.ini'", L"NGS2B", NULL);
        return;
    }



    //DELIMBS
    newVal1 = ini.GetDoubleValue(L"DELIMB", L"globalDelimbMulp", 1.0f);
    highDelimbMulp = ini.GetDoubleValue(L"DELIMB", L"highDelimbMulp", 1.80f);
    guilthrowDmgMulp = ini.GetDoubleValue(L"DELIMB", L"guilthrowDmgMulp", 1.50f);
    scytheDelimbMulp = ini.GetDoubleValue(L"DELIMB", L"scytheDelimbMulp", 1.20f);
    enmaDelimbMulp = ini.GetDoubleValue(L"DELIMB", L"emnaDelimbMulp", 1.20f);
    femaleDelimbMulp = ini.GetDoubleValue(L"DELIMB", L"femaleDelimbMulp", 1.00f);
    masterEnemyDMGMulp = ini.GetDoubleValue(L"DELIMB", L"masterEnemyHPMulp", 1.80f);
    masterEnemyDmgReductionMulp = ini.GetDoubleValue(L"DELIMB", L"masterEnemyDmgReductionMulp", 2.00f);
    mentorEnemyDmgReductionMulp = ini.GetDoubleValue(L"DELIMB", L"mentorEnemyDmgReductionMulp", 1.00f);
    warriorEnemyDmgReductionMulp = ini.GetDoubleValue(L"DELIMB", L"warriorEnemyDmgReductionMulp", 1.00f);
    fsDelimbMulp = ini.GetDoubleValue(L"DELIMB", L"fsDelimbMulp", 1.50f);

    //MURAMASA
    //weaponUpgradeCost = static_cast<uint16_t>(ini.GetLongValue(L"SHOP", L"weaponUpgradeCost", 30000));

    //ENEMY HP MULP
    //reHPTable[0].hpMulp = ini.GetDoubleValue(L"WATERDRAGON", L"waterDragonHPMulp", 0.50f);

    //GRAPHICS
    //corpseTimerLycans = ini.GetDoubleValue(L"GRAPHICS", L"corpseTimerLycans", 1800.00f);
    //ng2Shine = ini.GetBoolValue(L"Graphics", L"shine", true);
    //bloomIntensity = ini.GetDoubleValue(L"Graphics", L"bloomIntensity", 0.25f);

    //ENEMY AI
    isNinjaGrabSpeed = ini.GetBoolValue(L"ENEMYAI", L"isNinjaGrabSpeed", false);
    greyNinjaGrabSpeed = ini.GetBoolValue(L"ENEMYAI", L"greyNinjaGrabSpeed", false);
    zedGrabSpeed = ini.GetBoolValue(L"ENEMYAI", L"zedGrabSpeed", false);
    vangelfGrabSpeed = ini.GetBoolValue(L"ENEMYAI", L"vangelfGrabSpeed", false);
    lizGrabSpeedTail = ini.GetBoolValue(L"ENEMYAI", L"lizGrabSpeedTail", true);
    tripleIS = ini.GetBoolValue(L"ENEMYAI", L"tripleIS", true);
    isNinjaDodgeBlockChance = static_cast<BYTE>(ini.GetLongValue(L"ENEMYAI", L"isNinjaDodgeBlockChance", 100));
    isFiendNinjaDodgeBlockChance = static_cast<BYTE>(ini.GetLongValue(L"ENEMYAI", L"isFiendNinjaDodgeBlockChance", 100));
    lizDodgeBlockChance = static_cast<BYTE>(ini.GetLongValue(L"ENEMYAI", L"lizDodgeBlockChance", 100));
    izunaRecoveryPunish = ini.GetBoolValue(L"ENEMYAI", L"punishIzunaRecovery", true);

    //AUDIO
    mainMenuTrack = static_cast<BYTE>(ini.GetLongValue(L"AUDIO", L"mainMenuTrack", 0x52));
    ch1HeroTrack = static_cast<BYTE>(ini.GetLongValue(L"AUDIO", L"ch1HeroTrack", 0x3D));
    ch14HeroTrack = static_cast<BYTE>(ini.GetLongValue(L"AUDIO", L"ch14HeroTrack", 0x4D));
    //configChime = ini.GetBoolValue(L"AUDIO", L"configChime", true);

    //GAMEPLAY
    //animationSmoothing = ini.GetBoolValue(L"GAMEPLAY", L"animationSmoothing", true);
    //quickSelectBlur = ini.GetBoolValue(L"GAMEPLAY", L"quickSelectBlur", false);
     microStutter = static_cast<BYTE>(ini.GetLongValue(L"GAMEPLAY", L"hitstop", 0x00));
     storyHPCC = ini.GetBoolValue(L"GAMEPLAY", L"storyHPCC", true);
    //whiteFlash = ini.GetBoolValue(L"GAMEPLAY", L"whiteFlash", true);
    //disableEssence = ini.GetBoolValue(L"GAMEPLAY", L"disableEssence", false);
    //hasFullAirborneIframes = ini.GetBoolValue(L"GAMEPLAY", L"hasFullAirborneIframes", false);
    //ultimateNinja = ini.GetBoolValue(L"GAMEPLAY", L"UltimateNinja", false);
     etChargeTime = ini.GetDoubleValue(L"GAMEPLAY", L"etChargeTime", 50.00);
     utChargeTime = ini.GetDoubleValue(L"GAMEPLAY", L"utChargeTime", 110.00);


    ////CAMERA
    fovValue = ini.GetDoubleValue(L"CAMERA", L"fov", 0.13f);
    isFreeCamIzunaOnly = ini.GetBoolValue(L"CAMERA", L"isFreeCamIzunaOnly", true);
    isFreeCamAll = ini.GetBoolValue(L"CAMERA", L"isFreeCamAll", false);
    cameraHitImpact = ini.GetBoolValue(L"CAMERA", L"cameraHitImpact", true);

    ////DANGER ZONE
    //instantResume = ini.GetBoolValue(L"DANGERZONE", L"instantResume", false);

    //DEBUG
    //noClip = ini.GetBoolValue(L"DEBUG", L"noClip", false);
    freezeEnemies = ini.GetBoolValue(L"DEBUG", L"freezeEnemies", false);
    //disableDelimb = ini.GetBoolValue(L"DEBUG", L"disableDelimb", false);
    //windowAlwaysReadInputs = ini.GetBoolValue(L"DEBUG", L"windowAlwaysReadInputs", false);

    ////SPAWN
    ch1RasetsuDisableMinions = ini.GetBoolValue(L"SPAWN", L"ch1RasetsuDisableMinions", false);
    ch2RasetsuDisableMinions = ini.GetBoolValue(L"SPAWN", L"ch2RasetsuDisableMinions", false);
    ch14RasForDoppler = ini.GetBoolValue(L"SPAWN", L"ch14RasForDoppler", false);
    //skipCH1StatueEncOne = ini.GetBoolValue(L"SPAWN", L"skipCH1StatueEncOne", false);
    //skipCH4Statue = ini.GetBoolValue(L"SPAWN", L"skipCH4Statue", false);



    ////INTERFACE
    //vibrantMainMenu = ini.GetBoolValue(L"INTERFACE", L"vibrantMainMenu", true);
    //saveLastFrame = ini.GetBoolValue(L"INTERFACE", L"saveLastFrame", false);

    //// ATTACK CANCELS
    //CSimpleIniW::TNamesDepend keys;
    //ini.GetAllKeys(L"ATTACKCANCELS", keys);
    //attackCancelList.clear();

    //for (const auto& key : keys) {
    //    std::wstring value = ini.GetValue(L"ATTACKCANCELS", key.pItem, L"");

    //    if (!value.empty()) {

    //        std::wistringstream iss(value);
    //        std::wstring attackAnimStr, cancelAnimStr, cancelInputStr;

    //        std::getline(iss, attackAnimStr, L',');
    //        std::getline(iss, cancelAnimStr, L',');
    //        std::getline(iss, cancelInputStr, L',');


    //        attackCancelTable entry;
    //        entry.attackAnim = static_cast<uint16_t>(std::stoi(attackAnimStr, nullptr, 16));
    //        entry.cancelAnim = static_cast<uint16_t>(std::stoi(cancelAnimStr, nullptr, 16));
    //        entry.cancelInput = static_cast<uint32_t>(std::stoul(cancelInputStr, nullptr, 16));


    //        attackCancelList.push_back(entry);
    //    }
    //}
    //attackCancelListSize = attackCancelList.size();



}


bool compareMemory(DWORD_PTR address, const std::vector<unsigned char>& pattern) {
    if (IsBadReadPtr((void*)address, pattern.size())) {
        std::cerr << "Invalid memory address!" << std::endl;
        return false;
    }


    for (size_t i = 0; i < pattern.size(); ++i) {
        unsigned char* byteAddress = (unsigned char*)(address + i);
        if (*byteAddress != pattern[i]) {
            return false;
        }
    }
    return true;
}


HookInfo hooks[] = {
    //PATCH 1.0.0.6
    /*{0x144270A, 17, InjectTripleIS, "InjectTripleIS", &returnInjectTripleIS, 0},
    {0xFEA08A, 19, InjectDelimb1, "InjectDelimb1",&returnInjectDelimb1, 0},
    {0x1081B19, 14, InjectDelimb2, "InjectDelimb2",&returnInjectDelimb2, 0},
    {0x1000B76, 18, InjectAnim, "InjectAnim", &returnInjectAnim, 0},
    {0x1051901, 14, InjectFreeCam, "InjectFreeCam", &returnInjectFreeCam, 0},
    {0x171F1E5, 18, InjectInventoryCCNew, "InjectInventoryCCNew", &returnInjectInventoryCCNew,0},
    {0x174B001, 18, InjectC, "InjectC", &returnInjectC,0},
    {0x15F9114, 19, InjectSound, "InjectSound", &returnInjectSound, 0},
    {0x104A720, 17, InjectFOV, "InjectFOV", &returnInjectFOV, 0},
    {0x14E7C6D, 17, InjectDelimbFiends, "InjectDelimbFiends", &returnInjectDelimbFiends, 0},
    {0x17377D9, 15, InjectCLoop, "InjectCLoop", &returnInjectCLoop,0}*/
    //{0xF80C82, 18, InjectHalfCut, "InjectHalfCut", &returnInjectHalfCut,0} human gamemodule.dll+14E868E 


    //PATCH 1.0.0.7
    {0x144301A, 17, InjectTripleIS, "InjectTripleIS", &returnInjectTripleIS, 0},
    {0xFEA88A, 19, InjectDelimb1, "InjectDelimb1", &returnInjectDelimb1, 0},
    {0x10823A9, 14, InjectDelimb2, "InjectDelimb2", &returnInjectDelimb2, 0},
    {0x1001436, 18, InjectAnim, "InjectAnim", &returnInjectAnim, 0},
    {0x10521A1, 14, InjectFreeCam, "InjectFreeCam", &returnInjectFreeCam, 0},
    //{0x1720704, 18, InjectInventoryCCNew, "InjectInventoryCCNew", &returnInjectInventoryCCNew, 0},
    {0x15FA594, 19, InjectSound, "InjectSound", &returnInjectSound, 0},
    {0x104AFC0, 17, InjectFOV, "InjectFOV", &returnInjectFOV, 0},
    {0x17389B9, 15, InjectCLoop, "InjectCLoop", &returnInjectCLoop, 0},
    {0x14E8E2D, 17, InjectDelimbFiends, "InjectDelimbFiends", &returnInjectDelimbFiends, 0},
    {0x174B627, 19, InjectDisableSpawns, "InjectDisableSpawns", &returnInjectDisableSpawns},
    {0x17092DB, 15, InjectEntDie, "InjectEntDie", &returnInjectEntDie},
    {0x14E812C, 15, InjectHalfCutHuman, "InjectHalfCutHuman", &returnInjectHalfCutHuman},
    {0x15C4A07, 15, InjectEnemyDmgReduction, "InjectEnemyDmgReduction", &returnEnemyDmgReduction},
    //{0xFEA8FD, 19, InjectDelimb3, "InjectDelimb3", &returnInjectDelimb3, 0},
    {0x15C30F8, 15, InjectEntHitData,"InjectEntHitData", &returnInjectEntHitData,0},
    {0xFBF5AB, 15, InjectAIDodge, "InjectAIDodge", &returnInjectAIDodge, 0},
    {0xFF538D, 15, InjectRecoveryPunish, "InjectRecoveryPunish", &returnInjectRecoveryPunish,0},
    {0x15C3BBD,15, InjectIDrop, "InjectIDrop", &returnInjectIDrop,0},
    {0xFAB2E8, 16, InjectUTCharge,"InjectUTCharge", &returnInjectUTCharge,0},
    {0xB8409A, 16, InjectInput, "InjectInput", &returnInjectInput,0},
    {0xB843C6, 15, InjectLockCam, "InjectLockCam", &returnInjectLockCam,0},
    {0x103C8E7, 16, InjectCamShake, "InjectCamShake", &returnInjectCamShake,0}
    //{0x17552C4, 19, InjectDiffLoad, "InjectDiffLoad",& returnInjectDiffLoad}

    //{0xF80C82, 18, InjectHalfCut, "InjectHalfCut",& returnInjectHalfCut,0}


};

HookInfo hooksMasterNinjaOnly[] = {
    {0x174A5E1, 17, InjectCoords, "InjectCoords", &returnInjectCoords, 0},
    {0x174C531, 18, InjectC, "InjectC", &returnInjectC, 0},
    {0x173DC07, 17, InjectEventTrigger, "InjectEventTrigger", &returnInjectEventTrigger, 0 }


};
HookInfo hooksMentorOnly[] = {
    {0x174A5E1, 17, InjectCoordsMentor, "InjectCoordsMentor", &returnInjectCoords, 0},
    {0x174C531, 18, InjectCMentor, "InjectCMentor", &returnInjectC, 0},
    {0x173DC07, 17, InjectEventTriggerMentor, "InjectEventTriggerMentor", &returnInjectEventTrigger, 0 }


};
HookInfo hooksWarriorOnly[] = {
    {0x174A5E1, 17, InjectCoordsWarrior, "InjectCoordsWarrior", &returnInjectCoords, 0},
    {0x174C531, 18, InjectCWarrior, "InjectCWarrior", &returnInjectC, 0},
    {0x173DC07, 17, InjectEventTriggerWarrior, "InjectEventTriggerWarrior", &returnInjectEventTrigger, 0 }


};

bool Hook(void* hookAddress, void* myFunc, int len, int nopeLen = 0) {

    if (len < 14 && nopeLen <= 0) {
        return false;
    }

    DWORD oldProtect;
    VirtualProtect(hookAddress, len, PAGE_EXECUTE_READWRITE, &oldProtect);


    *(BYTE*)hookAddress = 0xFF;
    *((BYTE*)hookAddress + 1) = 0x25;
    *(DWORD*)((BYTE*)hookAddress + 2) = 0;
    *(DWORD_PTR*)((BYTE*)hookAddress + 6) = (DWORD_PTR)myFunc;

    if (nopeLen > 0) {
        for (int i = 0; i < nopeLen; i++) {
            *((BYTE*)hookAddress + len + i) = 0x90;
        }
    }

    VirtualProtect(hookAddress, len, oldProtect, &oldProtect);

    return true;
}




void ApplyHooks(HookInfo* hooks, int count, DWORD_PTR baseAddress) {
    for (int i = 0; i < count; i++) {
        DWORD_PTR hookAddress = baseAddress + hooks[i].offset;
        if (hooks[i].returnAddress) {
            *(hooks[i].returnAddress) = hookAddress + hooks[i].length;
        }
        if (!Hook((void*)hookAddress, hooks[i].hookFunction, hooks[i].length, hooks[i].nopeLen)) {
            std::stringstream ss;
            //ss << "Failed to hook: " << hooks[i].hookName << " at address: 0x" << std::hex << hookAddress;
            MessageBoxA(NULL, ss.str().c_str(), "Hook Error", MB_OK | MB_ICONERROR);
        }
    }
}



//MAYBE JUST MAKE ENUM SO SINGLE FUNCTION LOL
void WriteByte(DWORD_PTR address, BYTE value) {
    DWORD oldProtect;
    VirtualProtect((void*)address, sizeof(BYTE), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(BYTE*)address = value;
    VirtualProtect((void*)address, sizeof(BYTE), oldProtect, &oldProtect);
}
void WriteFloat(DWORD_PTR address, float value) {
    DWORD oldProtect;
    VirtualProtect((void*)address, sizeof(float), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(float*)address = value;
    VirtualProtect((void*)address, sizeof(float), oldProtect, &oldProtect);
}
void WriteFloats(DWORD_PTR *addresses, size_t size, FLOAT value) {
    for (size_t i = 0; i < size; i++) {
        DWORD_PTR addy = addresses[i] + baseAddress;
        DWORD oldProtect;
        VirtualProtect((void*)addy, sizeof(FLOAT), PAGE_EXECUTE_READWRITE, &oldProtect);
        *(FLOAT*)addy = value;
        VirtualProtect((void*)addy, sizeof(FLOAT), oldProtect, &oldProtect);

    }
}



void WriteMemory(void* address, const void* buffer, size_t size) {
    DWORD oldProtect;
    VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(address, buffer, size);
    VirtualProtect(address, size, oldProtect, &oldProtect);
}


void WriteEnemyHPMulp(uintptr_t startAddress, uintptr_t endAddress, float threshold, float dmgMulp) {
    DWORD oldProtect;
    VirtualProtect((void*)startAddress, (endAddress - startAddress), PAGE_EXECUTE_READWRITE, &oldProtect);

    for (uintptr_t currentAddress = startAddress; currentAddress <= endAddress; currentAddress += sizeof(float)) {
        float* ptr = (float*)currentAddress; 

        if (*ptr < threshold) {
            continue;  
        }

        *ptr = dmgMulp;  
    }
    VirtualProtect((void*)startAddress, (endAddress - startAddress), oldProtect, &oldProtect);
}

void ClearBattleTrackingData(unsigned int** battleData, size_t* battleTrackerAllSize, size_t battleDataSize) {
    for (size_t i = 0; i < battleDataSize; i++) {
        for (size_t j = 0; j < battleTrackerAllSize[i]; j++) {
            if (battleData[i]) {
                battleData[i][j] = 0;
            }
        }
    }
}

void ClearVars() {
    inventoryCCNew = false;
    cBattleRespawnCount = 0;
    cBattleRespawnCount2 = 0;
    cBattleRespawnCount3 = 0;
    cBattleRespawnCount4 = 0;
    cBattleRespawnCount5 = 0;
    cBattleRespawnCount6 = 0;
    cBattleRespawnCount7 = 0;
    cBattleRespawnCount8 = 0;
    cBattleRespawnCount9 = 0;
    cManualSpawnResetCounter = 0;
    cDeleteEnemy = 0;
    //CH4
    chp4MuesumBtlCounter = 0;
    chp4MuesumBtlCounterMentor = 0;
    chp4MuesumBtlCounterWarrior = 0;
    //CH6
    chp6RebirthBtlCounter = 0;
    chp6SecondSaveBtlCounter = 0;
    chp6RebirthBtlCounterMentor = 0;
    chp6SecondSaveBtlCounterMentor = 0;
    chp6RebirthBtlCounterWarrior = 0;
    chp6SecondSaveBtlCounterWarrior = 0;
    chp6WindmillBtlCounter = 0;
    chp6WindmillBtlCounterMentor = 0;
    chp6WindmillBtlCounterWarrior = 0;

    entHitInfo.address = 0;
    entHitInfo.ID = 0;
    entHitInfo.Playerstate = 0;

    canWaterDragonAttacks = 0;
    canWaterDragonOT = false;
    waterDragonBattleStart = 0;
    waterDragonDived = false;
    canSwapCoords = false;

    ClearBattleTrackingData(masterMasterBattleTrackers, masterMasterBattleTrackersSize, masterMasterBattleTrackersCount);
    ClearBattleTrackingData(warriorWarriorBattleTrackers, warriorWarriorBattleTrackersSize, warriorWarriorBattleTrackersCount);

   
}
void ApplyHelpers(DWORD_PTR baseAddress)
{
    DWORD_PTR hookAddress = baseAddress + 0xFDC3A6;
    if (freezeEnemies) {
        WriteByte(hookAddress, 0x90);
        WriteByte(hookAddress + 0x01, 0x90);
        WriteByte(hookAddress + 0x02, 0x90);
        WriteByte(hookAddress + 0x03, 0x90);
        WriteByte(hookAddress + 0x04, 0x90);
        WriteByte(hookAddress + 0x05, 0x90);
        WriteByte(hookAddress + 0x06, 0x90);
        WriteByte(hookAddress + 0x07, 0x90);
    }
    else {
        WriteByte(hookAddress, 0x41);
        WriteByte(hookAddress + 0x01, 0xFF);
        WriteByte(hookAddress + 0x02, 0x94);
        WriteByte(hookAddress + 0x03, 0xC4);
        WriteByte(hookAddress + 0x04, 0x10);
        WriteByte(hookAddress + 0x05, 0x53);
        WriteByte(hookAddress + 0x06, 0x8C);
        WriteByte(hookAddress + 0x07, 0x01);
    }

}




DWORD WINAPI MainThread(LPVOID param) {
    Sleep(2000);

    baseAddress = (DWORD_PTR)GetModuleHandle(L"gamemodule.dll");

    //lopBaseAddress += 0x36AF90000;

    

    if (baseAddress == 0) {
        MessageBoxA(NULL, "Failed to get base address of modules. \nmod will not be applied", "ERROR", MB_OK);
        return 0;
    }

    std::mt19937 rng;
    std::uniform_int_distribution<int> dist{ 1, 100 };
    rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());


    returnInjectFreeCamCall += baseAddress;
    activeChapterAddress = baseAddress + activeChapterOffset;
    pHpAddress = baseAddress + pHpAddress;
    enemyAliveAddress = baseAddress + enemyAliveOffset;
    enemyAliveAddress2 = baseAddress + enemyAliveOffset2;
    playerIdentAddress1 = baseAddress + playerIdentOffset1;
    RecoveryPunishLeaAddress = baseAddress + RecoveryPunishLeaOffset;
    pAnimAddress = baseAddress + pAnimOffset;
    playerSurfaceTypeAddress = baseAddress + playerSurfaceTypeOffset;

    int hookCount = sizeof(hooks) / sizeof(HookInfo);
    ApplyHooks(hooks, hookCount, baseAddress);

    LoadConfig();

    WriteByte(baseAddress + microStutterOffset01, microStutter);
    WriteByte(baseAddress + microStutterOffset02, microStutter);

    //DELIMBS
   DWORD_PTR nopeAddy = baseAddress + 0xFEA86A;
    NopMemory((void*)nopeAddy, 2);
    nopeAddy = baseAddress + 0xFEA86C;
    NopMemory((void*)nopeAddy, 2);
   
    //DELIMB FS BUFF
    /*nopeAddy = baseAddress + 0xFEA8F3;
    NopMemory((void*)nopeAddy, 2);*/
    nopeAddy = baseAddress + 0xFEA837;
    NopMemory((void*)nopeAddy, 6);

    //SCYTHE DELIMB FIX
    nopeAddy = baseAddress + 0xFEA0D0;
    NopMemory((void*)nopeAddy, 6);

    //IS ACCURACY
    DWORD_PTR hookAddress = baseAddress + 0x1460487;
    WriteByte(hookAddress, 0xEB);
    //DELIMB FS MULP 
    //hookAddress = baseAddress + 0xFEA8F9;
    //WriteByte(hookAddress, 0x93);
    
    ////DMG MULP scythe delimb gamemodule.dll+FEA0C9 
    //uintptr_t startAddress = baseAddress + 0x1EAACF8;
    //uintptr_t endAddress = baseAddress + 0x1EAAF74;
    /*if (masterEnemyDMGMulp > 0.00f){ */WriteFloats(masterEnemyHPMulpAddress, masterEnemyHPMulpAddressSize, masterEnemyDMGMulp); //} //WriteEnemyHPMulp(startAddress, endAddress, 2.00f, masterEnemyDMGMulp) ; }

    //CCSTORYHP
    if (storyHPCC) { WriteByte(baseAddress + 0x1701738, 0xEB); }

    ApplyHelpers(baseAddress);

    while (true) {

        WORD playerHP = *(WORD*)(baseAddress + 0x3380DB6);
        BYTE currentDiff = *(BYTE*)(baseAddress + activeDiffOffset);
        randomNum = dist(rng);



        if (playerHP <= 0) { 
            ClearVars(); 
        }

      

        
        if (diffInjected != currentDiff) {
            switch (currentDiff) {
            case 4: {
                diffInjected = currentDiff;
                ApplyHooks(hooksMasterNinjaOnly, sizeof(hooksMasterNinjaOnly) / sizeof(HookInfo), baseAddress);
                ClearVars();
                break;
            }
            case 3: {
                diffInjected = currentDiff;
                ApplyHooks(hooksMentorOnly, sizeof(hooksMentorOnly) / sizeof(HookInfo), baseAddress);
                ClearVars();
                break;
            }
            case 2: {
                diffInjected = currentDiff;
                ApplyHooks(hooksWarriorOnly, sizeof(hooksWarriorOnly) / sizeof(HookInfo), baseAddress);
                ClearVars();
                break;
            }
            }
        }













        if (GetAsyncKeyState(0x26) & 0x8000) {
            // MessageBoxA(NULL, "TEST", "ERROR", MB_OK);
            LoadConfig();
            ApplyHelpers(baseAddress);

            WriteByte(baseAddress + microStutterOffset01, microStutter);
            WriteByte(baseAddress + microStutterOffset02, microStutter);
            /*if (masterEnemyDMGMulp > 0.00f) { */WriteFloats(masterEnemyHPMulpAddress, masterEnemyHPMulpAddressSize, masterEnemyDMGMulp); //}//WriteEnemyHPMulp(startAddress, endAddress, 2.00f, masterEnemyDMGMulp); }

            if (storyHPCC) {
                WriteByte(baseAddress + 0x1701738, 0xEB);
            }
            else {
                WriteByte(baseAddress + 0x1701738, 0x74);
            }
        }
            
            
            
        



        Sleep(10);

    }

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved) {

    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hinstDLL, 0, 0);
        break;

    }

    return true;
}








































































