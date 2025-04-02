#include "pch.h"
#include "globals.h"
#include "functions.h"
#include "spawndata.h"
#include "mentor.h"

#pragma region MENTOR
void  __attribute__((naked))InjectCoordsMentor() {

    __asm__ volatile(".intel_syntax noprefix;"
        //ORIGINAL CODE
        "mov dword ptr [rsp + 0x2C], 00000000;"
        "movaps xmm0, [rsp + 0x20];"
        "movdqu[rdi], xmm0;"

        "push rax;"
        "push rbx;"
        "push rcx;"//SPAWN COORDS
        "push rdx;"//TRACKER
        "push rsi;"
        "push rdi;"//FREE TO USE AFTER LEVEL CHECK
        "push rbp;"

        "xor rbx,rbx;"
        "xor rdi,rdi;"

        "mov rax, qword ptr [rip + baseAddress];"
        "mov rbx, qword ptr [rip + activeDiffOffset];"

        //DIFF CHECK
        "cmp byte ptr [rax + rbx],0x03;"
        "jne exitInjectCoords; "

        //LEVEL CHECK
        "mov rdi, qword ptr [rip + activeChapterAddress];"
        "cmp rdi,rax;"
        "jle exitInjectCoords; "

        "mov rbp, qword ptr [rsp + 0x40];"//CURRENT BATTLE

        //CHAPTER 1
        "lea rcx, qword ptr [rip + masterninjabtlCH1SpawnCoords];"
        "lea rdx, qword ptr [rip + masterninjabtlCH1Tracker];"
        "lea rsi, qword ptr [rip + masterninjaCH1OriginalSpawnTriggerOffsets];"


        "cmp word ptr [rdi],0x0006;"
        "je coordsChapterOneMaster;"

        //CHAPTER 2
        "lea rcx, qword ptr [rip + masterninjabtlCH2SpawnCoords];"
        "lea rdx, qword ptr [rip + masterninjabtlCH2Tracker];"
        "lea rsi, qword ptr [rip + masterninjaCH2OriginalSpawnTriggerOffsets];"


        "cmp word ptr [rdi],0x0007;"
        "je coordsChapterTwoMaster;"

        //CHAPTER 3
        "lea rcx, qword ptr [rip + masterninjabtlCH3SpawnCoords];"
        "lea rdx, qword ptr [rip + masterninjabtlCH3Tracker];"
        "lea rsi, qword ptr [rip + masterninjaCH3OriginalSpawnTriggerOffsets];"


        "cmp word ptr [rdi],0x0008;"
        "je coordsChapterThreeMaster;"

        //CHAPTER 4
        "lea rcx, qword ptr [rip + masterninjabtlCH4SpawnCoords];"
        "lea rdx, qword ptr [rip + masterninjabtlCH4Tracker];"
        "lea rsi, qword ptr [rip + masterninjaCH4OriginalSpawnTriggerOffsets];"


        "cmp word ptr [rdi],0x0009;"
        "je coordsChapterFourMaster;"

        //CHAPTER 6
        "lea rcx, qword ptr [rip + masterninjabtlCH6SpawnCoords];"
        "lea rdx, qword ptr [rip + masterninjabtlCH6Tracker];"
        "lea rsi, qword ptr [rip + masterninjaCH6OriginalSpawnTriggerOffsets];"


        "cmp word ptr [rdi],0x000A;"
        "je coordsChapterSixMaster;"

        //CHAPTER 14
        "lea rcx, qword ptr [rip + masterninjabtlCH14SpawnCoords];"
        "lea rdx, qword ptr [rip + masterninjabtlCH14Tracker];"
        "lea rsi, qword ptr [rip + masterninjaCH14OriginalSpawnTriggerOffsets];"


        "cmp word ptr [rdi],0x0010;"
        "je coordsChapterFourteenMaster;"



        "jmp exitInjectCoords; "

        //CHAPTER 1
        "coordsChapterOneMaster:"

        //SECOND SAVE POINT BATTLE
        "mov rdi, qword ptr [rsi + 0x10];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH01;"

        //2ND LAST SAVE IS NINJA (OG2 HALLWAY RESTORED SPAWN)
        "mov rdi, qword ptr [rsi + 0x28];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH01;"

        //RASETSU
        "mov rdi, qword ptr [rsi + 0x30];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH01RAS;"

        "jmp exitInjectCoords; "

        "coordsCH01:"
        "cmp DWORD PTR[rdx + 0x02 * 0x04], 0x0101;"
        "je coordsCH01b;"

        "cmp DWORD PTR[rdx], 0x0101;"
        "je coordsCH01a;"

        "jmp exitInjectCoords;"

        //SECOND SAVE POINT BATTLE
        "coordsCH01a:"
        "movaps xmm10, [rcx];"
        "cmp byte ptr [rip+cBattleRespawnCount],0x01;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x10];"
        "cmp byte ptr [rip+cBattleRespawnCount],0x02;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x20];"
        "cmp byte ptr [rip+cBattleRespawnCount],0x03;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x30];"
        "cmp byte ptr [rip+cBattleRespawnCount],0x04;"
        "jle setCoords;"
        "movaps xmm10, [rcx];"
        "jmp setCoords;"


        //2ND LAST SAVE IS NINJA (OG2 HALLWAY RESTORED SPAWN)
        "coordsCH01b:"
        "movaps xmm10, [rcx + 0xF0];"
        "jmp setCoords;"

        //RASETSU
        "coordsCH01RAS:"
        "cmp DWORD PTR[rdx+0x04*0x04], 0x0101;"
        "jne exitInjectCoords;"
        "inc byte ptr [rip + cBattleRespawnCount5];"
        "movaps xmm10, [rcx+0x110];"
        "cmp byte ptr [rip + cBattleRespawnCount5],0x01;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x120];"
        "cmp byte ptr [rip + cBattleRespawnCount5],0x02;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x130];"
        "cmp byte ptr [rip + cBattleRespawnCount5],0x03;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x140];"
        "mov byte ptr [rip+cBattleRespawnCount5],0x00;"
        "jmp setCoords;"

        //CHAPTER 2
        "coordsChapterTwoMaster:"

        //NG2 CAVE
        "mov rdi, qword ptr [rsi];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH201;"

        "jmp exitInjectCoords; "

        "coordsCH201:"
        //RASETSU
        "cmp DWORD PTR[rdx + 0x04 * 0x04], 0x0101;"
        "je coordsCH203;"
        //SUPRISE AMBUSH
        "cmp DWORD PTR[rdx + 0x02 * 0x04], 0x0101;"
        "je coordsCH202;"
        
            "jmp exitInjectCoords; "
            
        ////CAVE (NOT NEEDED)
        //"cmp DWORD PTR[rdx], 0x0101;"
        //"jne exitInjectCoords;"
        //"movaps xmm10, [rcx+0x10];"
        //"jmp setCoords;"

        "coordsCH202:"
        "movaps xmm10, [rcx+0x30];"
        "cmp byte ptr [rip + cBattleRespawnCount7],0x01;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x40];"
        "jmp setCoords;"

        "coordsCH203:"
        "movaps xmm10, [rcx+0x50];"
        "jmp setCoords;"

        //CHAPTER 3
        "coordsChapterThreeMaster:"

        //VANGELF GOLD BEFORE SAVE WHERE YOU MONKEY CLIMB TO MURAMASA
        "mov rdi, qword ptr [rsi + 0x10];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH301;"

        "jmp exitInjectCoords; "

        "coordsCH301:"
        "cmp DWORD PTR[rdx + 0x02 * 0x04], 0x0101;"
        "jne exitInjectCoords;"
        "movaps xmm10, [rcx+0x130];"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x01;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x140];"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x02;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x150];"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x03;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x160];"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x05;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x170];"
        "jmp setCoords;"


        //CHAPTER 4
        "coordsChapterFourMaster:"

        //FOURTH SAVE IS ROOM MUESUM
        "mov rdi, qword ptr [rsi];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH401;"

        "jmp exitInjectCoords; "

        "coordsCH401:"
        "cmp DWORD PTR[rdx], 0x0101;"
        "jne exitInjectCoords;"
        "movaps xmm10, [rcx+0x40];"
        "cmp byte ptr [rip + randomNum,0x21;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x30];"
        "cmp byte ptr [rip + randomNum],0x42;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x20];"
        "jmp setCoords;"

        //CHAPTER 6
        "coordsChapterSixMaster:"

        //FIRST BATTLE why do I have this lol?
        /* "mov rdi, qword ptr [rsi];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH601;"*/

        //BRIDGE AFTER FIRST BATTLE (03) TALISMAN REBIRTH IS
        "mov rdi, qword ptr [rsi + 0x08];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH601;"

        "jmp exitInjectCoords; "

        "coordsCH601:"
        //WINDMILL WATER
        "cmp DWORD PTR[rdx + 0x02 * 0x04], 0x0101;"
        "je coordsCH602;"
        //BRIDGE AFTER FIRST BATTLE (03) TALISMAN REBIRTH IS
        "cmp DWORD PTR[rdx], 0x0101;"
        "jne exitInjectCoords;"
        "movaps xmm10, [rcx];"
        "jmp setCoords;"

        "coordsCH602:"
        "movaps xmm10,[rcx+ 0x30];"
        "jmp setCoords;"

        //CHAPTER 14
        "coordsChapterFourteenMaster:"

        //CLAW ROOM
        "mov rdi, qword ptr [rsi];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH1401;"

        //AFTER RASETSU
        "mov rdi, qword ptr [rsi + 0x18];"
        "add rdi,rax;"

        "cmp rdi,rbp;"
        "je coordsCH1402;"

        "jmp exitInjectCoords;"

        "coordsCH1401:"
        "cmp DWORD PTR[rdx], 0x0101;"
        "jne exitInjectCoords;"
        "movaps xmm10, [rcx+0x100];"
        "cmp byte ptr [rip + cBattleRespawnCount], 0x01;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x110];"
        "cmp byte ptr [rip + cBattleRespawnCount], 0x02;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x120];"
        "cmp byte ptr [rip + cBattleRespawnCount], 0x03;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x130];"
        "cmp byte ptr [rip + cBattleRespawnCount], 0x04;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x100];"
        "cmp byte ptr [rip + randomNum], 0x19;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x110];"
        "cmp byte ptr [rip + randomNum], 0x32;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x120];"
        "cmp byte ptr [rip + randomNum], 0x4B;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x130];"
        "jmp setCoords;"

        "coordsCH1402:"
        "movaps xmm10, [rcx+0x190];"
        "cmp byte ptr [rip + randomNum], 0x32;"
        "jle setCoords;"
        "movaps xmm10, [rcx+0x1A0];"
        "jmp setCoords;"







        "setCoords:"
        "pop rbp;"
        "pop rdi;"
        "pop rsi;"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "movdqu[rdi], xmm10;"
        "jmp qword ptr [rip + returnInjectCoords];"



        "exitInjectCoords:"
        "pop rbp;"
        "pop rdi;"
        "pop rsi;"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "jmp qword ptr [rip + returnInjectCoords];"




        );
}


void  __attribute__((naked))InjectEventTriggerMentor() {

    __asm__ volatile(".intel_syntax noprefix;"

        "push rax;"
        "push rbx;"
        "push rcx;"
        "push rdx;"
        "push rdi;"
        "push rsi;"
        "push rbp;"
        "push r8;"
        "push r9;"
        "push r10;"
        "push r11;"
        "push r12;"
        "push r13;"
        "push r14;"
        "xorps xmm10, xmm10;"
        "xor rbp,rbp;"
        "xor rsi,rsi;"
        "mov r10,rbp;"
        "mov r12,rbp;"
        "mov r13,rbp;"
        "mov r14,rbp;"

        "mov rsi, qword ptr [rip + baseAddress];"
        "mov rbx, qword ptr [rip + activeDiffOffset];"

        //DIFF CHECK
        "cmp byte ptr [rsi + rbx],0x03;"
        "jne codecbattle;"

        //LEVEL CHECK
        "mov rdi, qword ptr [rip + activeChapterAddress];"

        "cmp rdi,rsi;"
        "jle codecbattle;"

        //PORTING THINGS DONT ASK LoL
        "mov rax, qword ptr [rip + activeChapterAddress];"

        //HP CHECK
        "cmp word ptr [rsi+0X3380DB6], 0x00;"
        "jz codecbattle;"



        //CHAPTER 1
        "lea r8, qword ptr [rip + masterninjabtlCH1BattleCoords];"
        "lea r9, qword ptr [rip + masterninjabtlCH1Tracker];"
        "lea rdi, qword ptr [rip +  masterninjabtlCH1DistanceThreshold]; "
        "lea rbx, qword ptr [rip + masterninjaCH1OriginalSpawnTriggerOffsets];"
        "mov r11,r8;"
        "mov rcx,0x00;"
        "mov rdx,0x16;"
        "cmp word ptr  [rax], 0x06; "
        "je cBtlLoopStart;"

        //CHAPTER 2
        "lea r8, qword ptr [rip + masterninjabtlCH2BattleCoords];"
        "lea r9, qword ptr [rip + masterninjabtlCH2Tracker];"
        "lea rdi, qword ptr [rip +  masterninjabtlCH2DistanceThreshold]; "
        "lea rbx, qword ptr [rip + masterninjaCH2OriginalSpawnTriggerOffsets];"
        "mov r11,r8;"
        "mov rcx,0x00;"
        "mov rdx,0x0A;"
        "cmp word ptr  [rax], 0x07; "
        "je cBtlLoopStart;"

        //CHAPTER 3
        "lea r8, qword ptr [rip + masterninjabtlCH3BattleCoords];"
        "lea r9, qword ptr [rip + masterninjabtlCH3Tracker];"
        "lea rdi, qword ptr [rip +  masterninjabtlCH3DistanceThreshold]; "
        "lea rbx, qword ptr [rip + masterninjaCH3OriginalSpawnTriggerOffsets];"
        "mov r11,r8;"
        "mov rcx,0x00;"
        "mov rdx,0x0A;"
        "cmp word ptr  [rax], 0x08; "
        "je cBtlLoopStart;"

        //CHAPTER 4
        "lea r8, qword ptr [rip + masterninjabtlCH4BattleCoords];"
        "lea r9, qword ptr [rip + masterninjabtlCH4Tracker];"
        "lea rdi, qword ptr [rip +  masterninjabtlCH4DistanceThreshold]; "
        "lea rbx, qword ptr [rip + masterninjaCH4OriginalSpawnTriggerOffsets];"
        "mov r11,r8;"
        "mov rcx,0x00;"
        "mov rdx,0x07;"
        "cmp word ptr  [rax], 0x09; "
        "je cBtlLoopStart;"

        //CHAPTER 6
        "lea r8, qword ptr [rip + masterninjabtlCH6BattleCoords];"
        "lea r9, qword ptr [rip + masterninjabtlCH6Tracker];"
        "lea rdi, qword ptr [rip +  masterninjabtlCH6DistanceThreshold]; "
        "lea rbx, qword ptr [rip + masterninjaCH6OriginalSpawnTriggerOffsets];"
        "mov r11,r8;"
        "mov rcx,0x00;"
        "mov rdx,0x07;"
        "cmp word ptr  [rax], 0x0A; "
        "je cBtlLoopStart;"

        //CHAPTER 10
        "lea r8, qword ptr [rip + masterninjabtlCH10BattleCoords];"
        "lea r9, qword ptr [rip + masterninjabtlCH10Tracker];"
        "lea rdi, qword ptr [rip +  masterninjabtlCH10DistanceThreshold]; "
        "lea rbx, qword ptr [rip + masterninjaCH10OriginalSpawnTriggerOffsets];"
        "mov r11,r8;"
        "mov rcx,0x00;"
        "mov rdx,0x0A;"
        "cmp word ptr  [rax], 0x0D; "
        "je cBtlLoopStart;"

        //CHAPTER 14
        "lea r8, qword ptr [rip + masterninjabtlCH14BattleCoords];"
        "lea r9, qword ptr [rip + masterninjabtlCH14Tracker];"
        "lea rdi, qword ptr [rip +  masterninjabtlCH14DistanceThreshold]; "
        "lea rbx, qword ptr [rip + masterninjaCH14OriginalSpawnTriggerOffsets];"
        "mov r11,r8;"
        "mov rcx,0x00;"
        "mov rdx,0x0A;"
        "cmp word ptr  [rax], 0x10; "
        "je cBtlLoopStart;"


        "jmp codecbattle;"

        "cBtlLoopStart:"
        "cmp rcx,rdx;"
        "ja codecbattle;"

        //DISTANCE THRESHOLD
        "movss xmm10,[rdi+rbp*4];"
        "inc rbp;"
        //X
        "movss xmm5,[r8+rcx*4];"
        "subss xmm5,[rsi+0x3174468];"
        "mulss xmm5, xmm5;"
        //inc rcx;"
        //Y
        "add rcx,0x01;"
        "movss xmm6,[r8+rcx*4];"
        "subss xmm6, [rsi+0x3174464];"
        "mulss xmm6,xmm6;"
        //Z
        //inc rcx
        "add rcx,0x01;"
        "movss xmm7,[r8+rcx*4];"
        "subss xmm7,[rsi+0x3174460];"
        "mulss xmm7,xmm7;"
        "addss xmm5,xmm6;"
        "addss xmm5,xmm7;"
        "sub rcx,0x02;"
        "movss xmm9,xmm10;"
        "xorps xmm10,xmm10;"
        "comiss xmm5,xmm10;"
        "je codecbattle;"
        "comiss xmm5,xmm9;"
        "jbe cTriggerEvent;"
        "add rcx,0x03;"
        "cmp rcx,rdx;"
        "jl cBtlLoopStart;"
        "jmp codecbattle;"

        "cTriggerEvent:"
        "mov r8,rsi;"
        "xor rsi,rsi;"
        "xor rdx,rdx;"

        //CHAPTER 1
        "cmp byte ptr [rax], 0x06; "
        "je cTriggerEventCH1;"

        //CHAPTER 2
        "cmp byte ptr [rax], 0x07; "
        "je cTriggerEventCH2;"

        //CHAPTER 3
        "cmp byte ptr [rax], 0x08; "
        "je cTriggerEventCH3;"

        //CHAPTER 4
        "cmp byte ptr [rax], 0x09; "
        "je cTriggerEventCH4;"

        //CHAPTER 6
        "cmp byte ptr [rax], 0x0A; "
        "je cTriggerEventCH6;"

        //CHAPTER 10
        "cmp byte ptr [rax], 0x0D; "
        "je cTriggerEventCH10;"

        //CHAPTER 14
        "cmp byte ptr [rax], 0x10; "
        "je cTriggerEventCH14;"

        "jmp codecbattle;"

#pragma region CHAPTER_1_MASTER_TRIGGER_EVENTS
        "cTriggerEventCH1:"

        //BATTLE 01
        "cmp rcx, 0x00;"
        "je cTriggerEventCH0101;"

        //FIRST SAVE
        "cmp rcx, 0x03;"
        "je cTriggerEventsDisable;"

        //SECOND SAVE
        "cmp rcx, 0x06;"
        "je cTriggerEventsDisable;"

        //SECOND LAST SAVE
        "cmp rcx, 0x09;"
        "je cTriggerEventsDisable;"

        //2ND LAST SAVE IS NINJA (DELETED OG2 HALLWAY SPAWN RESTORE)
        "cmp rcx, 0x0C;"
        "mov rdx,0x02;"
        "je cTriggerEventCH0102;"
        "cmp rcx, 0x0F;"
        "je cTriggerEventCH0102;"
        "cmp rcx, 0x12;"
        "je cTriggerEventCH0102;"

        //RASETSU
        "mov rdx,0x03;"
        "cmp rcx, 0x15;"
        "je cTriggerEventCH0103;"

        "jmp codecbattle;"

        "cTriggerEventCH0101:"
        //RED GATE OPENED?
        "mov rbx, qword ptr [rbx + 0x08];"
        "add rbx,r8;"
        "cmp byte ptr [rbx],0x00;"
        "jz codecbattle;"
        "cmp DWORD PTR [r9], 0x0F0F;"
        "je codecbattle;"
        "mov DWORD PTR [r9], 0x0101;"
        "mov rcx, [r9+0x04];"
        "jmp cStartTriggerEvent02;"

        //2ND LAST SAVE IS NINJA (DELETED OG2 HALLWAY SPAWN RESTORE)
        "cTriggerEventCH0102:"
        //PREVENT FROM RESPAWN AFTER SAVING
      /*  "mov rbx,0x6B92352;"
        "add rbx,r8;"
        "cmp byte ptr [rbx],0xFF;"
        "je codecbattle;"
        "mov rbx,0x6B92352;"*/
        "cmp byte ptr [r8 + 0x6B92340],0x0B;"
        "jae codecbattle;"
        "cmp DWORD PTR [r9 + 0x02 * 0x04], 0x0F0F;"
        "je codecbattle;"
        "mov DWORD PTR [r9 + 0x02 * 0x04], 0x0101;"
        "mov rcx, [r9 + 0x03 * 0x04];"
        "jmp cStartTriggerEvent02;"

        //RASETSU
        "cTriggerEventCH0103:"
        "jmp codecbattle;"
        "cmp byte ptr [rip + ch1RasetsuDisableMinions],0x00;"
        "jnz codecbattle;"
        "cmp byte ptr [r8 + 0x6B9EC10],0x07;"
        "jl codecbattle;"
        "cmp DWORD PTR [r9 + 0x04 * 0x04], 0x0F0F;"
        "je codecbattle;"
        "mov DWORD PTR [r9 + 0x04 * 0x04], 0x0101;"
        "mov rcx, [r9 + 0x05 * 0x04];"
        "jmp cStartTriggerEvent02;"
#pragma endregion
#pragma region CHAPTER_2_MASTER_TRIGGER_EVENTS
            "cTriggerEventCH2:"

            //CAVE
            "cmp rcx,0x00;"
            "je cTriggerEventCH201;"

            //SUPRISED AMBUSH BY BRIDGE
            "cmp rcx,0x03;"
            "mov rdx,0x02;"
            "je cTriggerEventCH202;"

            //FOURTH SAVE
            "cmp rcx,0x06;"
            "je cTriggerEventsDisable;"

            //RASETSU
            "cmp rcx,0x09;"
            "mov rdx,0x04;"
            "je cTriggerEventCH203;"

            "jmp codecbattle;"

            "cTriggerEventCH201:"
            "mov rdx, qword ptr [rbx + 0x10];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0xFF;"
            "je codecbattle;"
            "mov rdx, qword ptr [rbx + 0x08];"
            "add rdx,r8;"
            "mov byte ptr [rdx],0x01;"
            "cmp DWORD PTR [r9], 0x0F0F;"
            "je codecbattle;"
            "mov DWORD PTR [r9], 0x0101;"
            "mov rcx, [r9+0x04];"
            "jmp cStartTriggerEvent02;"

            "cTriggerEventCH202:"
            "mov rdx, qword ptr [rbx + 0x18];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0xFF;"
            "je codecbattle;"
            "mov rdx, qword ptr [rbx + 0x08];"
            "add rdx,r8;"
            "mov byte ptr [rdx],0x01;"
            "cmp DWORD PTR [r9 + 0x02 * 0x04], 0x0F0F;"
            "je codecbattle;"
            "mov DWORD PTR [r9 + 0x02 * 0x04], 0x0101;"
            "mov rcx, [r9 + 0x03 * 0x04];"
            "jmp cStartTriggerEvent02;"


            "cTriggerEventCH203:"
            //CONFIG INI MINION CHECK
            "cmp byte ptr [rip + ch2RasetsuDisableMinions],0x00;"
            "jnz codecbattle;"
            //VERIFY BATTLE STARTED FIRST
            "mov rdx, qword ptr [rbx + 0x28];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0x00;"
            "jz codecbattle;"
            //VERIFY BATTLE COMPLETED (GATE OPENED)
            "mov rdx, qword ptr [rbx + 0x30];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0x01;"
            "je codecbattle;"
            "mov rdx, qword ptr [rbx + 0x20];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0xFF;"
            "je codecbattle;"
            "mov rdx, qword ptr [rbx + 0x08];"
            "add rdx,r8;"
            "mov byte ptr [rdx],0x01;"
            "cmp DWORD PTR [r9 + 0x04 * 0x04], 0x0F0F;"
            "je codecbattle;"
            "mov DWORD PTR [r9 + 0x04 * 0x04], 0x0101;"
            "mov rcx, [r9 + 0x05 * 0x04];"
            "jmp cStartTriggerEvent02;"


#pragma endregion
#pragma region CHAPTER_3_MASTER_TRIGGER_EVENTS
        "cTriggerEventCH3:"

        //BATTLE 1 - DOGS (NG2 VANGELF GAUNTLET)
        "cmp rcx,0x00;"
        "je cTriggerEventCH301;"

        //BATTLE DISABLE - BATTLE 1 AND PRIOR
        "cmp rcx,0x03;"
        "je cTriggerEventsDisable;"

        //AFTER FIRST MURAMASA AFTER WINDBLADE DELETED SPAWN POINT
        "mov rdx,0x02;"
        "cmp rcx,0x06;"
        "je cTriggerEventCH302;"

        "jmp codecbattle;"

        "cTriggerEventCH301:"
        "mov rbx, qword ptr [rbx + 0x08];"
        "add rbx,r8;"
        "cmp byte ptr [rbx],0x00;"
        "jz codecbattle;"
        "cmp DWORD PTR [r9], 0x0F0F;"
        "je codecbattle;"
        "mov DWORD PTR [r9], 0x0101;"
        "mov rcx, [r9+0x04];"
        "jmp cStartTriggerEvent02;"

        //AFTER FIRST MURAMASA AFTER WINDBLADE DELETED SPAWN POINT
        "cTriggerEventCH302:"
        //PREVENT PREVIOUS SPAWNS FROM DISABLING AFTER GOING PAST MURAMASA DOOR
        "mov rbx, qword ptr [rbx + 0x18];"
        "add rbx,r8;"
        "mov byte ptr [rbx],0x01;"
        "cmp byte ptr [r8 + 0x6B53B20],0x0C;"
        "jae codecbattle;"
        "cmp DWORD PTR [r9 + 0x02 * 0x04], 0x0F0F;"
        "je codecbattle;"
        "mov DWORD PTR [r9 + 0x02 * 0x04], 0x0101;"
        "mov rcx, [r9 + 0x03 * 0x04];"
        "jmp cStartTriggerEvent02;"

#pragma endregion

#pragma region CHAPTER_4_MASTER_TRIGGER_EVENTS
        "cTriggerEventCH4:"

        //FOURTH SAVE IS ROOM
        "cmp rcx,0x00;"
        "je cTriggerEventCH401;"
        "cmp rcx,0x03;"
        "je cTriggerEventCH401;"
        "cmp rcx,0x06;"
        "je cTriggerEventCH401;"

        "jmp codecbattle;"

        "cTriggerEventCH401:"
        "mov rdx, qword ptr [rbx + 0x10];"
        "add rdx,r8;"
        "cmp byte ptr [rdx],0xFF;"
        "je codecbattle;"
        "mov rdx, qword ptr [rbx + 0x08];"
        "add rdx,r8;"
        "mov byte ptr [rdx],0x01;"
        "cmp DWORD PTR [r9], 0x0F0F;"
        "je codecbattle;"
        "mov DWORD PTR [r9], 0x0101;"
        "mov rcx, [r9+0x04];"
        "jmp cStartTriggerEvent02;"


#pragma endregion

#pragma region CHAPTER_6_MASTER_TRIGGER_EVENTS
                "cTriggerEventCH6:"

                //IS NINJA REBIRTH
                "cmp rcx,0x00;"
                "je cTriggerEventCH601;"

                "mov rdx,0x02;"

                //WINDMILL
                "cmp rcx,0x03;"
                "je cTriggerEventCH602;"

                //THIRD SAVE
                "cmp rcx,0x06;"
                "je cTriggerEventsDisable;"

                "jmp codecbattle;"

                "cTriggerEventCH601:"
                //BATTLE ALREADY COMPLETED?
                "mov rdx, qword ptr [rbx + 0x18];"
                "add rdx,r8;"
                "cmp byte ptr [rdx],0xFF;"
                "je codecbattle;"
                //DONT DISABLE TRIGGER (RE-ENABLE)
                "mov rdx, qword ptr [rbx + 0x10];"
                "add rdx,r8;"
                "mov byte ptr [rdx],0x01;"
                //START EVENT TRIGGER
                "cmp DWORD PTR [r9], 0x0F0F;"
                "je codecbattle;"
                "mov DWORD PTR [r9], 0x0101;"
                "mov rcx, [r9+0x04];"
                "jmp cStartTriggerEvent02;"

                "cTriggerEventCH602:"
                //PLAYER ON WATER SURFACE?
                "mov rdx, qword ptr [rip + playerSurfaceTypeAddress];"
                "cmp byte ptr [rdx],0x04;"
                "jl codecbattle;"
                //BATTLE ALREADY COMPLETED?
                "mov rdx, qword ptr [rbx + 0x20];"
                "add rdx,r8;"
                "cmp byte ptr [rdx],0xFF;"
                "je codecbattle;"
                //DONT DISABLE TRIGGER (RE-ENABLE)
                "mov rdx, qword ptr [rbx + 0x10];"
                "add rdx,r8;"
                "mov byte ptr [rdx],0x01;"
                //START EVENT TRIGGER
                "cmp DWORD PTR [r9 + 0x02 * 0x04], 0x0F0F;"
                "je codecbattle;"
                "mov DWORD PTR [r9 + 0x02 * 0x04], 0x0101;"
                "mov rcx, [r9+0x03 * 0x04];"
                "jmp cStartTriggerEvent02;"


#pragma endregion

#pragma region CHAPTER_10_MASTER_TRIGGER_EVENTS
            "cTriggerEventCH10:"

            "cmp rcx, 0x00;"
            "je cTriggerEventCH101;"

            "cmp rcx, 0x03;"
            "je cTriggerEventCH101;"





            "jmp codecbattle;"


            "cTriggerEventCH101:"
            "mov rdx, qword ptr [rbx + 0x08];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0xFF;"
            "je codecbattle;"
            "mov rdx, qword ptr [rbx + 0x10];"
            "add rdx,r8;"
            "mov byte ptr [rdx],0x01;"
            "cmp DWORD PTR [r9], 0x0F0F;"
            "je codecbattle;"
            "mov DWORD PTR [r9], 0x0101;"
            "mov rcx, [r9+0x04];"
            "jmp cStartTriggerEvent02;"


#pragma endregion

#pragma region CHAPTER_14_MASTER_TRIGGER_EVENTS
            "cTriggerEventCH14:"

            //CLAW ROOM
            "cmp rcx,0x00;"
            "je cTriggerEventCH1401;"

            "cmp rcx,0x03;"
            "je cTriggerEventsDisable;"

            //AFTER RASETSU
            "cmp rcx,0x06;"
            "mov rdx,0x02;"
            "je cTriggerEventCH1402;"

            "cmp rcx,0x09;"
            "je cTriggerEventsDisable;"


            "jmp codecbattle;"

            "cTriggerEventCH1401:"
            "mov rdx, qword ptr [rbx + 0x10];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0xFF;"
            "je codecbattle;"
            "mov rdx, qword ptr [rbx + 0x08];"
            "add rdx,r8;"
            "mov byte ptr [rdx],0x01;"
            "cmp DWORD PTR [r9], 0x0F0F;"
            "je codecbattle;"
            "mov DWORD PTR [r9], 0x0101;"
            "mov rcx, [r9+0x04];"
            "jmp cStartTriggerEvent02;"

            "cTriggerEventCH1402:"
            "mov rdx, qword ptr [rbx + 0x28];"
            "add rdx,r8;"
            "cmp byte ptr [rdx],0xFF;"
            "je codecbattle;"
            "mov rdx, qword ptr [rbx + 0x20];"
            "add rdx,r8;"
            "mov byte ptr [rdx],0x01;"
            "cmp DWORD PTR [r9 + 0x02 * 0x04], 0x0F0F;"
            "je codecbattle;"
            "mov DWORD PTR [r9 + 0x02 * 0x04], 0x0101;"
            "mov rcx, [r9 + 0x03 * 0x04];"
            "jmp cStartTriggerEvent02;"


#pragma endregion




        //RESET SPAWN COUNTERS
        "cTriggerEventsDisable:"
        "mov rbx, qword ptr [rip + enemyAliveAddress];"
        "cmp rsi, rdx;"
        "ja lookAheadBattle;"
        "mov dword ptr [r9 + rsi * 4], 0x0F0F;"
        "mov byte ptr [rip + cBattleRespawnCount], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount2], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount3], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount4], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount5], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount6], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount7], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount8], 0x00;"
        "mov byte ptr [rip + cBattleRespawnCount9], 0x00;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        //CH4
        "mov byte ptr [rip + chp4MuesumBtlCounterMentor], 0x00;"
        "add rsi, 0x02;"
        //CH6
        "mov byte ptr [rip + chp6RebirthBtlCounterMentor],0x00;"
        "mov byte ptr [rip + chp6SecondSaveBtlCounterMentor],0x00;"
        "mov byte ptr [rip + chp6WindmillBtlCounterMentor],0x00;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "jmp cTriggerEventsDisable;"

        "lookAheadBattle:"
        "test r14,r14;"
        "jz codecbattle;"
        "xor r14, r14;"
        "cmp byte ptr [rbx], 0x00;"
        "jnz codecbattle;"
        "mov rdx, r13;"
        "cmp r12, 0x0000;"
        "jz codecbattle;"
        "jmp cTriggerEventsDisable;"


        "cStartTriggerEvent:"
        "mov rdi, 0x00000000FFFFFFFF;"
        "and rcx, rdi;"
        "add r8, rcx;"
        "mov dword ptr [r8], 0x01000100;"
        "jmp codecbattle;"
        "cStartTriggerEvent02:"
        "mov rdi, 0x00000000FFFFFFFF;"
        "and rcx, rdi;"
        "add r8, rcx;"
        "mov byte ptr[r8], 01;"
        "mov byte ptr[r8 + 02], 01;"
        "jmp codecbattle;"

        "codecbattleSave:"
        "add rbx,r8;"
        "mov byte ptr [rbx],0xFF;"


        "codecbattle:"
        "pop r14;"
        "pop r13;"
        "pop r12;"
        "pop r11;"
        "pop r10;"
        "pop r9;"
        "pop r8;"
        "pop rbp;"
        "pop rsi;"
        "pop rdi;"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        //ORIGINAL CODE
        "add rbx, rdi;"
        "movzx ecx, byte ptr[rbx + 0x000001F0];"
        "movzx ebp, byte ptr[rbx + 0x000001F3];"
        "jmp qword ptr [rip + returnInjectEventTrigger];"




        );
}

void  __attribute__((naked))InjectCMentor() {

    __asm__ volatile(".intel_syntax noprefix;"



        //ORIGINAL
        "movzx edi, byte ptr [rdx];"
        "mov rsi,rcx;"
        "movzx ebp, byte ptr [rdx+0x01];"
        "xor r12d,r12d;"
        "movzx r14d,word ptr [rdx+0x04];"

        "push rax;"//ACTIVE SPAWN TRIGGERED COMPARE
        "push rbx;"
        "push rcx;"
        "push rdx;"
        "push rsi;"
        "push rdi;"
        "push r8;"
        "push r9;"
        "push r10;"
        "push r11;"
        "push r12;"
        "push r13;"
        "push r15;"

        "xor r11,r11;"
        "xor r12,r12;"
        "xor r13,r13;"
        "xor r15,r15;"

        "mov r9,qword ptr [rip+baseAddress];"
        "mov rbx, qword ptr [rip + activeDiffOffset];"

        //DIFF CHECK
        "cmp byte ptr [r9 + rbx],0x03;"
        "jne exitInjectC;"

        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "xor r8,r8;"

        //LEVEL CHECK
        "mov rsi, qword ptr [rip + activeChapterAddress];"

        //ENEMIES ALIVE ADDRESS
        "mov r10, qword ptr [rip + enemyAliveAddress];"
        "mov r12, qword ptr [rip + enemyAliveAddress2];"

        //CHAPTER 1
        "lea r8, qword ptr [rip+masterninjabtlCH1Tracker];"
        "lea rbx, qword ptr [rip + masterninjaCH1OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x06;"
        "je chapter1Master;"

        "xor r8,r8;"

        //CHAPTER 2
        "lea r8, qword ptr [rip+masterninjabtlCH2Tracker];"
        "lea rbx, qword ptr [rip + masterninjaCH2OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x07;"
        "je chapter2Master;"

        "xor r8,r8;"

        //CHAPTER 3
        "lea r8, qword ptr [rip+masterninjabtlCH3Tracker];"
        "lea rbx, qword ptr [rip + masterninjaCH3OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x08;"
        "je chapter3Master;"

        "xor r8,r8;"

        //CHAPTER 4
        "lea r8, qword ptr [rip+masterninjabtlCH4Tracker];"
        "lea rbx, qword ptr [rip + masterninjaCH4OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x09;"
        "je chapter4Master;"

        "xor r8,r8;"

        //CHAPTER 6
        "lea r8, qword ptr [rip+masterninjabtlCH6Tracker];"
        "lea rbx, qword ptr [rip + masterninjaCH6OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x0A;"
        "je chapter6Master;"

        "xor r8,r8;"

        //CHAPTER 10
        "lea r8, qword ptr [rip+masterninjabtlCH10Tracker];"
        "lea rbx, qword ptr [rip + masterninjaCH10OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x0D;"
        "je chapter10Master;"

        "xor r8,r8;"

        //CHAPTER 13
        "cmp byte ptr [rsi],0x0F;"
        "je chapter13Master;"


        "xor r8,r8;"

        //CHAPTER 14
        "lea r8, qword ptr [rip+masterninjabtlCH14Tracker];"
        "lea rbx, qword ptr [rip + masterninjaCH14OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x10;"
        "je chapter14Master;"


        "jmp exitInjectC;"

#pragma region CHAPTER_1_MASTER_SPAWNS
        "chapter1Master:"

        //ORIGINAL = BATTLE 2 | USED FOR = RESTORING NG2 ARCHERS AFTER RED GATE
        "mov rdi,[rbx + 0x10];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP0101;"

        //FIRST BATTLE AFTER THIRD SAVE
        "mov rdi,[rbx + 0x18];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP01SAKURA;"

        //BATTLE RIGHT BEFORE BUDDAH
        "mov rdi,[rbx + 0x20];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP01BUDDAHBEFORE;"

        //2ND LAST SAVE IS NINJA (HALLWAY OG2 RESTORED SPAWN)
        "mov rdi,[rbx + 0x28];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP0101;"

        //RASETSU
        "mov rdi,[rbx + 0x30];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP0101;"

        "jmp exitInjectC;"

        "setEnemyCHP0101:"
        "cmp dword ptr [r8 + 0x04 * 0x04], 0x0101;"
        "je setEnemyCHP01RAS;"

        "cmp dword ptr [r8 + 0x02 * 0x04], 0x0101;"
        "je setEnemyCHP01HALLWAYOG2;"

        "cmp dword ptr [r8], 0x0101;"
        "je setenemyCHP01NG2RedGate;"

        "jmp exitInjectC;"

        //NG2 RED GATE SPAWN
        "setenemyCHP01NG2RedGate:"
        "mov byte ptr [rip+cDeleteEnemy],0x01;"
        "mov dword ptr [r8],0x0F0F;"
        "cmp byte ptr [rip+cBattleRespawnCount],0x04;"
        "ja spawnTacOneRocket;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "mov byte ptr [rip+canSpawn],0x01;"
        "inc byte ptr [rip+cBattleRespawnCount];"
        "mov dword ptr [r8],0x0101;"
        "jmp spawnTacOneRocket;"

        //FIRST BATTLE AFTER THIRD SAVE
        "setEnemyCHP01SAKURA:"
        "inc byte ptr [rip+cManualSpawnResetCounter];"
        "mov byte ptr [rip+canSpawn],0x01;"
        "cmp byte ptr [rip+cManualSpawnResetCounter],0x02;"
        "jle spawnTacOneRocket;"
        "cmp byte ptr [rip+cManualSpawnResetCounter],0x07;"
        "jle spawnTacNinja;"
        //"mov byte ptr [rip+cManualSpawnResetCounter],0x00;"
        "jmp spawnTacNinja;"

        //BATTLE RIGHT BEFORE BUDDAH
        "setEnemyCHP01BUDDAHBEFORE:"
        "inc byte ptr [rip+cBattleRespawnCount3];"
        "cmp byte ptr [rip+cBattleRespawnCount3],0x02;"
        "jle spawnTacOneRocketActive;"
        "jmp spawnTacNinjaRed;"

        //2ND LAST SAVE IS NINJA (HALLWAY OG2 RESTORED SPAWN)
        "setEnemyCHP01HALLWAYOG2:"
        "mov byte ptr [rip+cDeleteEnemy],0x01;"
        "mov dword ptr [r8 + 0x02 * 0x04],0x0F0F;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "mov byte ptr [rip+canSpawn],0x01;"
        "inc byte ptr [rip+cBattleRespawnCount4];"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x05;"
        "ja spawnTacNinja;"
        "mov dword ptr [r8 + 0x02 * 0x04],0x0101;"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x01;"
        "jle spawnTacNinja;"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x03;"
        "jle spawnISNinja;"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x05;"
        "jle spawnTacNinja;"
        "jmp spawnTacNinja;"

        //RASETSU
        "setEnemyCHP01RAS:"
        "cmp DWORD PTR [r8 + 0x04 * 0x04], 0x0101;"
        "jne exitInjectC;"
        "mov BYTE PTR [rip + cDeleteEnemy], 0x01;"
        //COME BACK AFTER PATCH ENEMY ALIVE USE GLOBAL VAR
        "cmp BYTE PTR [r10], 0x06;"
        "ja exitInjectC;"
        "cmp BYTE PTR [r12], 0x07;"
        "ja exitInjectC;"
        "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
        "mov DWORD PTR [r8 + 0x04 * 0x04], 0x0101;"
        "jmp spawnISNinja;"



#pragma endregion

#pragma region CHAPTER_2_MASTER_SPAWNS
            "chapter2Master:"

            //CAVE AND SUPRISE AMBUSH
            "mov rdi,[rbx];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP201;"


            "jmp exitInjectC;"

            "setEnemyCHP201:"
            //RASETSU
            "cmp DWORD PTR [r8 + 0x04 * 0x04], 0x0101;"
            "je setEnemyCHP203;"
            //SUPRISE AMBUSH
            "cmp DWORD PTR [r8 + 0x02 * 0x04], 0x0101;"
            "je setEnemyCHP202;"
            //CAVE
            "cmp DWORD PTR [r8], 0x0101;"
            "jne exitInjectC;"
            "mov byte ptr [rip+cDeleteEnemy],0x01;"
            "mov dword ptr [r8],0x0F0F;"
            "mov r11, qword ptr [rbx + 0x10];"
            "cmp byte ptr [rip+cBattleRespawnCount6],0x02;"
            "ja disableEnemyEvent;"
            "mov byte ptr [rip+cDeleteEnemy],0x00;"
            "mov byte ptr [rip+canSpawn],0x01;"
            "inc byte ptr [rip+cBattleRespawnCount6];"
            "mov dword ptr [r8],0x0101;"
            "jmp spawnTacNinja;"

            "setEnemyCHP202:"
            "mov byte ptr [rip+cDeleteEnemy],0x01;"
            "mov dword ptr [r8 + 0x02 * 0x04],0x0F0F;"
            "mov r11, qword ptr [rbx + 0x18];"
            "cmp byte ptr [rip+cBattleRespawnCount7],0x02;"
            "ja disableEnemyEvent;"
            "inc byte ptr [rip + cBattleRespawnCount7];"
            "mov byte ptr [rip+cDeleteEnemy],0x00;"
            "mov byte ptr [rip+canSpawn],0x01;"
            "mov dword ptr [r8 + 0x02 * 0x04],0x0101;"
            "cmp byte ptr [rip + cBattleRespawnCount7],0x02;"
            "jle spawnISNinja;"
            "jmp spawnTacOneRocket;"

            "setEnemyCHP203:"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x01;"
            "mov DWORD PTR [r8 + 0x04 * 0x04], 0x0F0F;"
            "mov r11, qword ptr [rbx + 0x20];"
            "cmp BYTE PTR [rip + cBattleRespawnCount8], 0x1F;"
            "ja disableEnemyEvent;"
            "mov DWORD PTR [r8 + 0x04 * 0x04], 0x0101;"
            "cmp BYTE PTR [r10], 0x03;"
            "ja exitInjectC;"
            "cmp BYTE PTR [r12], 0x04;"
            "ja exitInjectC;"
            "inc BYTE PTR [rip + cBattleRespawnCount8];"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
            "jmp spawnMagePurple;"






#pragma endregion

#pragma region CHAPTER_3_MASTER_SPAWNS
        "chapter3Master:"

        //BATTLE 1 - REPLACE DOG WITH OG2 GAUNTLET
        "mov rdi,[rbx];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP301;"

        //BEFORE MURAMASA NEAR SAVE (GOLD VANGELF) RESPAWN AFTER FIRST WINDMILL
        "mov rdi,[rbx+0x10];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP302;"

        "jmp exitInjectC;"

        "setEnemyCHP301:"
        "cmp DWORD PTR [r8], 0x0101;"
        "jne exitInjectC;"
        "mov BYTE PTR [rip + cDeleteEnemy], 0x01;"
        "cmp BYTE PTR [r10], 0x05;"
        "jae exitInjectC;"
        "cmp BYTE PTR [r12], 0x06;"
        "jae exitInjectC;"
        "mov DWORD PTR [r8], 0x0F0F;"
        "cmp BYTE PTR [rip + cBattleRespawnCount], 0x1F;"
        "jae exitInjectC;"
        "inc BYTE PTR [rip + cBattleRespawnCount];"
        "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
        "mov DWORD PTR [r8], 0x0101;"
        "jmp spawnRedRobot;"

        "setEnemyCHP302:"
        "cmp dword ptr [r8 + 0x02 * 0x04],0x0101;"
        "jne exitInjectC;"
        "mov byte ptr [rip+cDeleteEnemy],0x01;"
        "mov dword ptr [r8 + 0x02 * 0x04],0x0F0F;"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x08;"
        "ja spawnISNinja;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "mov byte ptr [rip+canSpawn],0x01;"
        "inc byte ptr [rip+cBattleRespawnCount2];"
        "mov dword ptr [r8 + 0x02 * 0x04],0x0101;"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x01;"
        "jle spawnTacOneRocket;"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x02;"
        "jle spawnTacOneRocket;"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x03;"
        "jle spawnTacOneRocket;"
        "cmp byte ptr [rip+cBattleRespawnCount2],0x05;"
        "jmp spawnISNinja;"

#pragma endregion

#pragma region CHAPTER_4_MASTER_SPAWNS
        "chapter4Master:"

        //FOURTH SAVE - IS ROOM MUESUM
        "mov rdi,[rbx];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP401;"

        //SUBWAY VANGELF
        "mov rdi,[rbx + 0x18];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP403;"

        //SUBWAY VANGELF
        "mov rdi,[rbx + 0x20];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP403;"

        //SUBWAY VANGELF
        "mov rdi,[rbx + 0x28];"
        "add rdi,r9;"
        "cmp rcx,rdi;"
        "je setEnemyCHP403;"

        ////AFTER ENMA PICKUP, NEXT ROOM WITH TORCH (9C)
        //"mov rdi,[rbx + 0x30];"
        //"add rdi,r9;"
        //"cmp rcx,rdi;"
        //"je setEnemyCHP404;"


        "jmp exitInjectC;"

        "setEnemyCHP401:"
        "mov byte ptr [rdx + 0x14], 0x00;"
        "mov r11, qword ptr [rbx + 0x10];"
        "lea rsi, qword ptr [rip + chp4MuesumSpawnMentor];"
        "mov rcx, [rip + chp4MuesumSpawnSizeMentor];"
        "lea r15, qword ptr [rip + chp4MuesumBtlCounterMentor];"
        "movzx r13, byte ptr [rip + chp4MuesumBtlMaxSpawnCapMentor];"
        "jmp spawnEnemyOnlyWaveAliveOne;"

        "setEnemyCHP403:"
        "inc byte ptr [rip + cBattleRespawnCount8];"
        "cmp byte ptr [rip + cBattleRespawnCount8],0x01;"
        "jle spawnVangelfGreenFly;"
        "mov byte ptr [rip + cBattleRespawnCount8],0x00;"
        "jmp spawnVangelfJump;"

        "setEnemyCHP404:"
        "inc byte ptr [rip + cBattleRespawnCount];"
        "cmp byte ptr [rip + cBattleRespawnCount],0x01;"
        "jle spawnMage;"
        "mov byte ptr [rip + cBattleRespawnCount],0x00;"
        "jmp spawnISNinja;"


#pragma endregion

#pragma region CHAPTER_6_MASTER_SPAWNS
            "chapter6Master:"

            //FIRST BATTLE
            "mov rdi,[rbx];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP601;"

            //IS REBIRTH + //WINDMILL
            "mov rdi,[rbx + 0x08];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP602;"

            //SECOND SAVE
            "mov rdi,[rbx + 0x28];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP603;"

            //TOO LAZY
            "cmp r14,0x0B2;"
            "je chp6GhostFish;"

            "cmp r14,0x039;"
            "jne exitInjectC;"
            "mov byte ptr [rdx + 0x14],0x03;"
            "mov byte ptr [rdx + 0x1C],0x03;"


            "jmp exitInjectC;"

            "chp6GhostFish:"
            "mov byte ptr [rdx + 0x14],0x04;"
            "mov byte ptr [rdx + 0x1C],0x06;"
            "jmp exitInjectC;"

            "setEnemyCHP601:"
            "mov byte ptr [rip+canspawn2],0x01;"
            "inc byte ptr [rip+cBattleRespawnCount];"
            "cmp byte ptr [rip+cBattleRespawnCount],0x05;"
            "jle spawnTacNinjaRed;"
            "mov byte ptr [rip+canspawn2],0x00;"
            "jmp spawnTacNinjaRed;"

            //IS REBIRTH
            "setEnemyCHP602:"
            "cmp dword ptr [r8 + 0x02 * 0x04],0x0101;"
            "je setEnemyCHP602a;"
            "cmp dword ptr [r8],0x0101;"
            "jne exitInjectC;"
            //BATTLE COMPLETED MARKER
            "mov r11, qword ptr [rbx + 0x18];"
            "lea rsi, qword ptr [rip + chp6RebirthSpawnMentor];"
            "mov rcx, [rip + chp6RebirthSpawnSizeMentor];"
            "lea r15, qword ptr [rip + chp6RebirthBtlCounterMentor];"
            "movzx r13, byte ptr [rip + chp6RebirthBtlMaxSpawnCapMentor];"
            "jmp spawnEnemyOnlyWaveAliveOne;"

            //WINDMILL
            "setEnemyCHP602a:"
            "mov byte ptr [rdx + 0x14], 0x09;"
            //BATTLE TRACKER OFFSET
            "mov r12,0x02;"
            "mov r11, qword ptr [rbx + 0x20];"
            "lea rsi, qword ptr [rip + chp6WindmillSpawnMentor];"
            "mov rcx, [rip + chp6WindmillSpawnSizeMentor];"
            "lea r15, qword ptr [rip + chp6WindmillBtlCounterMentor];"
            "movzx r13, byte ptr [rip + chp6WindmillBtlMaxSpawnCapMentor];"
            "jmp spawnEnemyOnlyWaveAliveOneFixed;"

            "setEnemyCHP603:"
            "lea rsi, qword ptr [rip + chp6SecondSaveAmbushSpawnMentor];"
            "mov rcx, [rip + chp6SecondSaveAmbushSpawnSizeMentor];"
            "lea r15, qword ptr [rip + chp6SecondSaveBtlCounterMentor];"
            "jmp spawnEnemyOnlyNoWave;"






#pragma endregion

#pragma region CHAPTER_10_MASTER_SPAWNS
            "chapter10Master:"

            //FOURTH SAVE - IS ROOM MUESUM
            "mov rdi,[rbx];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP101;"

         

            "jmp exitInjectC;"

            "setEnemyCHP101:"
            "cmp DWORD PTR[r8], 0x0101;"
            "jne exitInjectC;"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x01;"
            "cmp BYTE PTR [r10], 0x03;"
            "jae exitInjectC;"
            "mov DWORD PTR [r8], 0x0F0F;"
            "cmp BYTE PTR [rip + cBattleRespawnCount], 0x0A;"
            "jae disableEnemyCHP101;"
            "inc BYTE PTR [rip + cBattleRespawnCount];"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
            "mov DWORD PTR [r8], 0x0101;"
            //"mov word ptr [rdx + 0x64],0xA040;"
            "jmp spawnFlyingRobot;"

            "disableEnemyCHP101:"
            "mov rbx, [rbx + 0x08];"
            "add rbx,r9;"
            "mov byte ptr [rbx],0xFF;"
            "jmp exitInjectC;"


#pragma endregion

#pragma region CHAPTER_13_MASTER_SPAWNS
        "chapter13Master:"

        //STAIRS
        "cmp cx,0xC0F8;"
        "je setEnemyCHP1301;"

        "cmp cx,0xD0B8;"
        "je setEnemyCHP1301;"

        "cmp cx,0xEA50;"
        "je setEnemyCHP1301;"

        "cmp cx,0xFA10;"
        "je setEnemyCHP1301;"

        "cmp cx,0x13A8;"
        "je setEnemyCHP1301;"

        "cmp cx,0x2368;"
        "je setEnemyCHP1301;"


        "jmp exitInjectC;"

        "setEnemyCHP1301:"
        "inc byte ptr [rip+cBattleRespawnCount9];"
        "cmp byte ptr [rip+cBattleRespawnCount9],0x01;"
        "jle spawnISNinjaN;"
        "cmp byte ptr [rip+cBattleRespawnCount9],0x04;"
        "jle spawnGreyNinja;"
        "mov byte ptr [rip+cBattleRespawnCount9],0x00;"
        "jmp spawnGreyNinja;"




#pragma endregion

#pragma region CHAPTER_14_MASTER_SPAWNS
            "chapter14Master:"

            //CLAW ROOM
            "mov rdi,[rbx];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP1401;"

            //AFTER RASETSU
            "mov rdi,[rbx + 0x18];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP1402;"

            "cmp r14, 0x0104;"
            "jne exitInjectC;"

            "cmp byte ptr [rip + ch14RasForDoppler],0x00;"
            "jz exitInjectC;"

           /* "cmp bx,0x2560;"
            "jne exitInjectC;"*/

            "mov r14,0x00A5;"
            "mov [rdx+0x04], r14d;"
            "mov word ptr [rdx + 0x64],0x7060;"



            "jmp exitInjectC;"


            "jmp exitInjectC;"

            "setEnemyCHP1401:"
            "cmp DWORD PTR [r8], 0x0101;"
            "jne exitInjectC;"
            "cmp BYTE PTR [r10], 0x05;"
            "jae setEnemyCHP1401a;"
            "cmp BYTE PTR [rip + cBattleRespawnCount],0x05;"
            "jae setEnemyCHP1401a;"
            "inc byte ptr [rip + cBattleRespawnCount];"
            "jmp spawnFiendIS;"

            "setEnemyCHP1401a:"
            "mov byte ptr [rip + cBattleRespawnCount],0x05;"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x01;"
            "cmp byte ptr [r10],0x06;"
            "jae exitInjectC;"
            "mov DWORD PTR [r8], 0x0F0F;"
            "cmp BYTE PTR [rip + cBattleRespawnCount2], 0x10;"
            "jae disableEnemyCHP1401a;"
            "inc BYTE PTR [rip + cBattleRespawnCount2];"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
            "mov DWORD PTR [r8], 0x0101;"
            "jmp spawnFiendIS;"

            "disableEnemyCHP1401a:"
            "mov rbx, [rbx + 0x10];"
            "add rbx,r9;"
            "mov byte ptr [rbx],0xFF;"
            "jmp exitInjectC;"

            "setEnemyCHP1402:"
            "cmp DWORD PTR [r8 + 0x02 * 0x04], 0x0101;"
            "jne exitInjectC;"
            "cmp BYTE PTR [r10], 0x06;"
            "ja setEnemyCHP1402a;"
            "cmp BYTE PTR [r12], 0x07;"
            "ja setEnemyCHP1402a;"
            "cmp BYTE PTR [rip + cBattleRespawnCount3],0x07;"
            "jae setEnemyCHP1402a;"
            "inc byte ptr [rip + cBattleRespawnCount3];"
            "cmp byte ptr [rip + cBattleRespawnCount3],0x01;"
            "jle spawnFiendMageN;"
            "cmp byte ptr [rip + cBattleRespawnCount3],0x03;"
            "jle spawnFiendGrey;"
            "jmp spawnFiendIS;"

            "setEnemyCHP1402a:"
            "mov byte ptr [rip + cBattleRespawnCount3],0x07;"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x01;"
            "cmp byte ptr [r10],0x06;"
            "ja exitInjectC;"
            "cmp BYTE PTR [r12], 0x07;"
            "ja exitInjectC;"
            "mov DWORD PTR [r8 + 0x02 * 0x04], 0x0F0F;"
            "cmp BYTE PTR [rip + cBattleRespawnCount4], 0x10;"
            "jae disableEnemyCHP1402a;"
            "inc BYTE PTR [rip + cBattleRespawnCount4];"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
            "mov DWORD PTR [r8 + 0x02 * 0x04], 0x0101;"
            "cmp BYTE PTR [rip + cBattleRespawnCount4],0x01;"
            "jle spawnFiendMageN;"
            "cmp BYTE PTR [rip + cBattleRespawnCount4],0x03;"
            "jle spawnFiendGrey;"
            "cmp BYTE PTR [rip + cBattleRespawnCount4],0x06;"
            "jle spawnFiendIS;"
            "mov BYTE PTR [rip + cBattleRespawnCount4],0x00;"
            "jmp spawnFiendIS;"

            //PUT OFFSET IN REGISTER SO I CAN JUST HAVE ONE CODE FOR ALL BATTLES DUMBASS BUT NOT IMPORTANT RIGHT NOW LOL
            "disableEnemyCHP1402a:"
            "mov rbx, [rbx + 0x28];"
            "add rbx,r9;"
            "mov byte ptr [rbx],0xFF;"
            "jmp exitInjectC;"


#pragma endregion



        "disableEnemyEvent:"
        "add r11,r9;"
        "mov byte ptr [r11],0xFF;"
        "jmp exitInjectC;"

        "spawnMage:"
        "mov r14d,0xA1;"
        "mov byte ptr [rdx + 0x04], 0xA1;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"


        "spawnRasetsu:"
        "mov r14d,0x23;"
        "mov byte ptr [rdx + 0x04], 0x23;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnRasetsuRed:"
        "mov r14d,0xA5;"
        "mov byte ptr [rdx + 0x04], 0xA5;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"


        "spawnGreyNinja:"
        "mov byte ptr [rdx+0x04],0x9D;"
        "mov byte ptr [rdx+0x1C],0x03;"
        "mov byte ptr[rdx + 0x2C], 0xFF;"
        "mov byte ptr[rdx + 0x30], 0xFF;"
        "mov byte ptr[rdx + 0x31], 0xFF;"
        "mov byte ptr[rdx + 0x38], 0xFF;"
        "mov byte ptr[rdx + 0x3C], 0xFF;"
        "mov byte ptr[rdx + 0x3D], 0xFF;"
        "mov r14,0x9D;"
        "jmp exitInjectC;"

        "spawnMagePurple:"
        "mov byte ptr [rdx+0x04],0x28;"
        "mov byte ptr [rdx+0x1C],0x03;"
        "mov byte ptr[rdx + 0x2C], 0xFF;"
        "mov byte ptr[rdx + 0x30], 0xFF;"
        "mov byte ptr[rdx + 0x31], 0xFF;"
        "mov byte ptr[rdx + 0x38], 0xFF;"
        "mov byte ptr[rdx + 0x3C], 0xFF;"
        "mov byte ptr[rdx + 0x3D], 0xFF;"
        "mov r14,0x28;"
        "jmp exitInjectC;"


        "spawnBrownNinja:"
        "mov byte ptr [rdx+0x04],0x08;"
        "mov byte ptr [rdx+0x1C],0x03;"
        "mov byte ptr[rdx + 0x2C], 0xFF;"
        "mov byte ptr[rdx + 0x30], 0xFF;"
        "mov byte ptr[rdx + 0x31], 0xFF;"
        "mov byte ptr[rdx + 0x38], 0xFF;"
        "mov byte ptr[rdx + 0x3C], 0xFF;"
        "mov byte ptr[rdx + 0x3D], 0xFF;"
        "mov r14,0x08;"
        "jmp exitInjectC;"

        "spawnISNinja:"
        "mov r14d,0x9C;"
        "mov byte ptr [rdx + 0x04], 0x9C;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnFiendIS:"
        "mov r14d,0x70;"
        "mov byte ptr [rdx + 0x04], 0x70;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnFiendGrey:"
        "mov r14d,0x2F;"
        "mov byte ptr [rdx + 0x04], 0x2F;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnFiendMageN:"
        "mov r14d,0x7C;"
        "mov byte ptr [rdx + 0x04], 0x7C;"
        "mov byte ptr [rdx+0x1C], 0x1C;"
        "jmp exitInjectC;"

        "spawnVangelf:"
        "mov r14d,0x03;"
        "mov byte ptr [rdx + 0x04], 0x03;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnVangelfGreen:"
        "mov r14d,0x75;"
        "mov byte ptr [rdx + 0x04], 0x75;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"


        "spawnVangelfGoldFly:"
        "mov r14d,0xA7;"
        "mov byte ptr [rdx + 0x04], 0xA7;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x14], 0x09;"
        "jmp exitInjectC;"

        "spawnGajaRed:"
        "mov r14d,0x9E;"
        "mov byte ptr [rdx + 0x04], 0x9E;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnRedRobot:"
        "mov r14d,0x1C;"
        "mov byte ptr [rdx + 0x04], 0x1C;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnGreyninjabow: "
        "mov byte ptr [rdx+0x04], 0x9D;"
        "mov byte ptr [rdx+0x1C], 0x05;"
        "mov byte ptr [rdx+0x2C], 0x03;"
        "mov byte ptr [rdx+0x30], 0x28;"
        "mov byte ptr [rdx+0x31], 0x00;"
        "mov byte ptr [rdx+0x38], 0x04;"
        "mov byte ptr [rdx+0x3C], 0x29;"
        "mov byte ptr [rdx+0x3D], 0x00;"
        "mov r14d,0x9D;"
        "jmp exitInjectC;"

        "spawnTacOneRocket:"
        "mov byte ptr [rdx+0x04], 0x38;"
        "mov byte ptr [rdx+0x1C], 0x05;"
        "mov byte ptr [rdx+0x2C], 0x01;"
        "mov byte ptr [rdx+0x30], 0x3D;"
        "mov byte ptr [rdx+0x31], 0x00;"
        "mov byte ptr [rdx+0x38], 0x02;"
        "mov byte ptr [rdx+0x3C], 0x3E;"
        "mov byte ptr [rdx+0x3D], 0x00;"
        "mov r14,0x38;"
        "jmp exitInjectC;"

        "spawnTacOneRocketActive:"
        "mov byte ptr [rdx+0x04], 0x38;"
        "mov byte ptr [rdx+0x1C], 0x1C;"
        "mov byte ptr [rdx+0x2C], 0x01;"
        "mov byte ptr [rdx+0x30], 0x3D;"
        "mov byte ptr [rdx+0x31], 0x00;"
        "mov byte ptr [rdx+0x38], 0x02;"
        "mov byte ptr [rdx+0x3C], 0x3E;"
        "mov byte ptr [rdx+0x3D], 0x00;"
        "mov r14,0x38;"
        "jmp exitInjectC;"

        "spawnTacManyRocket:"
        "mov byte ptr [rdx+0x04], 0x38;"
        "mov byte ptr [rdx+0x1C], 0x05;"
        "mov byte ptr [rdx+0x2C], 0x01;"
        "mov byte ptr [rdx+0x30], 0x8B;"
        "mov byte ptr [rdx+0x31], 0x00;"
        "mov byte ptr [rdx+0x38], 0x02;"
        "mov byte ptr [rdx+0x3C], 0x8C;"
        "mov byte ptr [rdx+0x3D], 0x00;"
        "mov r14,0x38;"
        "jmp exitInjectC;"

        "spawnTacNinja:"
        "mov byte ptr [rdx+0x04],0x38;"
        "mov byte ptr [rdx+0x1C],0x03;"
        "mov byte ptr[rdx + 0x2C], 0xFF;"
        "mov byte ptr[rdx + 0x30], 0xFF;"
        "mov byte ptr[rdx + 0x31], 0xFF;"
        "mov byte ptr[rdx + 0x38], 0xFF;"
        "mov byte ptr[rdx + 0x3C], 0xFF;"
        "mov byte ptr[rdx + 0x3D], 0xFF;"
        "mov r14,0x38;"
        "jmp exitInjectC;"

        "spawnTacMeleeRed:"
        "mov byte ptr [rdx+0x04], 0x38;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x2C], 0xFF;"
        "mov byte ptr [rdx+0x30], 0xFF;"
        "mov byte ptr [rdx+0x31], 0xFF;"
        "mov byte ptr [rdx+0x38], 0xFF;"
        "mov byte ptr [rdx+0x3C], 0xFF;"
        "mov byte ptr [rdx+0x3D], 0xFF;"
        "mov byte ptr [rdx+0x24], 0x02;"
        "mov r14,0x38;"
        "jmp exitInjectC;"

        "spawnTacNinjaRed:"
        "mov byte ptr [rdx+0x04], 0x38;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x2C], 0xFF;"
        "mov byte ptr [rdx+0x30], 0xFF;"
        "mov byte ptr [rdx+0x31], 0xFF;"
        "mov byte ptr [rdx+0x38], 0xFF;"
        "mov byte ptr [rdx+0x3C], 0xFF;"
        "mov byte ptr [rdx+0x3D], 0xFF;"
        "mov byte ptr [rdx+0x24], 0x02;"
        "mov r14,0x38;"
        "jmp exitInjectC;"

        "spawnFlyingRobot:"
        "mov byte ptr [rdx+0x04],0x1D;"
        "mov byte ptr [rdx+0x1C],0x03;"
        "mov r14,0x1D;"
        "jmp exitInjectC;"

        "spawnISNinjaN:"
        "mov r14d,0x9C;"
        "mov byte ptr [rdx + 0x04], 0x9C;"
        "mov byte ptr [rdx+0x1C], 0x1C;"
        "jmp exitInjectC;"



        "spawnVangelfGreenFly:"
        "mov r14d,0x75;"
        "mov byte ptr [rdx + 0x04], 0x75;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x14], 0x09;"
        "jmp exitInjectC;"

        "spawnVangelfJump:"
        "mov r14d,0x03;"
        "mov byte ptr [rdx + 0x04], 0x03;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x14], 0x01;"
        "jmp exitInjectC;"

        //NEW SPAWN SYSTEMS GO HERE      

        //SPAWN SYSTEM - WAVE BASED - ONLY ENEMY ID
        "spawnEnemyOnlyWaveAliveOne:"
        "cmp dword ptr [r8], 0x0101;"
        "jne exitInjectC;"
        "dec rcx;"
        "mov byte ptr [rip + cDeleteEnemy], 0x01;"
        //ACTIVE ALIVE ENEMIES CHECK
        "cmp byte ptr [r10], r13b;"
        "ja exitInjectC;"
        "mov dword ptr [r8], 0x0F0F;"
        //SPAWNS COMPLETED CHECK
        "xor rax,rax;"
        "mov rax, [r15];"
        "cmp rax, rcx;"
        "ja disableEnemyEvent;"
        //SPAWN ENEMY
        "mov r14w, word ptr [rsi + rax * 0x02];"
        "mov dword ptr [r8], 0x0101;"
        "mov [rdx + 0x04], r14w;"
        "inc byte ptr [r15];"
        "mov byte ptr [rip + cDeleteEnemy], 0x00;"
        "jmp exitInjectC;"

        //SPAWN SYSTEM - WAVE BASED - ONLY ENEMY ID
        "spawnEnemyOnlyWaveAliveOneFixed:"
        "cmp dword ptr [r8 + r12 * 0x04], 0x0101;"
        "jne exitInjectC;"
        "dec rcx;"
        "mov byte ptr [rip + cDeleteEnemy], 0x01;"
        //ACTIVE ALIVE ENEMIES CHECK
        "cmp byte ptr [r10], r13b;"
        "ja exitInjectC;"
        "mov dword ptr [r8 + r12 * 0x04], 0x0F0F;"
        //SPAWNS COMPLETED CHECK
        "xor rax,rax;"
        "mov rax, [r15];"
        "cmp rax, rcx;"
        "ja disableEnemyEvent;"
        //SPAWN ENEMY
        "mov r14w, word ptr [rsi + rax * 0x02];"
        "mov dword ptr [r8 + r12 * 0x04], 0x0101;"
        "mov [rdx + 0x04], r14w;"
        "inc byte ptr [r15];"
        "mov byte ptr [rip + cDeleteEnemy], 0x00;"
        "jmp exitInjectC;"

        //NO WAVE - TRIGGER BASED (ENEMY AMOUNT MUST BE SET IN DAT)
        "spawnEnemyOnlyNoWave:"
        "dec rcx;"
        //SPAWNS COMPLETED CHECK
        "xor rax,rax;"
        "mov rax, [r15];"
        "cmp rax, rcx;"
        "ja exitInjectC;"
        //SPAWN ENEMY
        "mov r14w, word ptr [rsi + rax * 0x02];"
        "mov [rdx + 0x04], r14w;"
        "inc byte ptr [r15];"
        "jmp exitInjectC;"

        "exitInjectC:"
        "pop r15;"
        "pop r13;"
        "pop r12;"
        "pop r11;"
        "pop r10;"
        "pop r9;"
        "pop r8;"
        "pop rdi;"
        "pop rsi;"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "mov byte ptr [rip + canSpawn],0x00;"
        "jmp qword ptr [rip + returnInjectC];"





        );
}
#pragma endregion
