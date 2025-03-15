#include "pch.h"
#include "globals.h"
#include "hook.h"
#include "functions.h"
#include "spawndata.h"

#pragma region GLOBAL_HOOKS

__attribute__((naked)) void InjectCamShake() {

    __asm(".intel_syntax noprefix;"
    ".intel_syntax noprefix;"
        "movaps[rsp + 0x000000E0], xmm7;"
        "push rax;"
        "mov rax, qword ptr [rip + baseAddress];"
        "cmp byte ptr [rip + cameraHitImpact],0x00;"
        "setz al;"

        "test al,al;"
        "jnz exitInjectCamShake;"
        
        "cmp word ptr [rax + 0x2F535D4],0x6F6F;"
        "jne exitInjectCamShake;"


        "mulss xmm0,[rax+0x2FC62D8];"
        "pop rax;"
        "jmp QWORD PTR [rip + returnInjectCamShake];"

        "exitInjectCamShake:"
        "pop rax;"
        "mulss xmm0,[rdi+0x00000090];"
        "jmp QWORD PTR [rip + returnInjectCamShake];"
        );
}

void  __attribute__((naked))InjectLockCam() {
    //ADD LOWER DIFF LATER
    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"
        "push rbx;"
        "push rcx;"
        "push rdx;"
        "xor rbx,rbx;"
        "xor rcx,rcx;"
        "xor rdx,rdx;"

        "mov rax, qword ptr [rip + baseAddress];"
        "mov rbx, [rip + lockcamAdd1];"

        "cmp word ptr [rax + rbx],0xFFFF;"
        "je exitLockCam;"

        "mov rcx, [rip + lockcamAdd2];"
       // "mov rdx, [rip + lockcamAdd3];"

        "cmp byte ptr [rdi+0x49],0x08;"
        "je unlockCam;"

        "cmp byte ptr [rdi+0x49],0x04;"
        "jne exitLockCam;"

        "mov byte ptr [rax + rcx],0x00;"
        //"mov byte ptr [rax + rdx],0x00;"

        "jmp exitLockCam;"

        "unlockCam:"
        "mov byte ptr [rax + rcx],0x02;"
        //"mov byte ptr [rax + rdx],0x02;"

        "exitLockCam:"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "movups xmm0,[rdi+0x48];"
        "movups [rax],xmm0;"
        "movups xmm1,[rdi+0x58];"
        "movups [rax+0x10],xmm1;"
        "jmp qword ptr [rip + returnInjectLockCam];"





        );
}

__attribute__((naked)) void InjectInput() {

    __asm(".intel_syntax noprefix;"
    ".intel_syntax noprefix;"
        "mov rdi,rcx;"
        "mov eax, [rcx + 0x48];"
        "mov [rcx + 0x54], eax;"
        "movzx ebx, byte ptr[rcx + 0x00000099];"
        "mov [rip + userInput], eax;"
        "jmp QWORD PTR [rip + returnInjectInput];"
        );
}

void  __attribute__((naked))InjectUTCharge() {

    __asm__ volatile(".intel_syntax noprefix;"
        "movss xmm1, [rip + etChargeTime];"
        "movss xmm2, [rip + utChargeTime];"
        "jmp qword ptr [rip + returnInjectUTCharge];"

        );
}


void  __attribute__((naked))InjectIDrop() {

    __asm__ volatile(".intel_syntax noprefix;"

        "movzx ecx, word ptr[r8 + 0x00009AE6];"
        "cmp r9w, cx;"
        "lea eax, [rdx + rcx];"
        "cmove ax, dx;"

        "push rbx;"
        "push rcx;" // ANIM TABLE
        "push rdi;" // COUNTER
        "push r8;"  
        "push r9;"  
        "push r10;"// ANIM FROM TABLE


        "test rax,rax;"
        "jz exitIDrop;"

        "cmp rax,0xFFFF;"
        "je exitIDrop;"

        //Already doing ent ID check so not really needed but doesn't hurt to be safe lol
        "mov rcx, qword ptr [rip + playerIdentAddress1];"
        "cmp rcx,rbx;"
        "jne iDropCanStart;"
        "jmp exitIDrop;"

        "iDropCanStart:"
        "cmp word ptr [rbx+0x20],0x009C;"
        "je iDropStart;"
        "cmp word ptr [rbx+0x20],0x009D;"
        "je iDropStart;"
        "cmp word ptr [rbx+0x20],0x0004;"
        "je iDropStart;"
        "cmp word ptr [rbx+0x20],0x0008;"
        "je iDropStart;"
        "cmp word ptr [rbx+0x20],0x0038;"
        "je iDropStart;"
        "cmp word ptr [rbx+0x20],0x00F1;"
        "je iDropStart;"


        "jmp exitIDrop;"


        "iDropStart:"
        "lea rcx, qword ptr [rip + iDropTable];"
        "mov r10, [rip + iDropTableSize];"
        "dec r10;"
        "xor rdi, rdi;"
        "xor r8, r8;"
        "xor r9, r9;"
        "mov rbx, qword ptr [rip + pAnimAddress];"

        "iDropLoop:"
        "cmp rdi, r10;"
        "ja exitIDrop;"
        "movzx r8, word ptr [rcx + rdi * 0x02];"
        "movzx r9, word ptr [rbx];"   
        "cmp r8, r9;"
        "je iDropKill;"
        "inc rdi;"
        "jmp iDropLoop;"

        "iDropKill:"
        "xor rdx,rdx;"
        

        "exitIDrop:"
        "pop r10;"
        "pop r9;"
        "pop r8;"
        "pop rdi;"
        "pop rcx;"
        "pop rbx;"
        "mov [r8+0x00009AC6],ax;"
        "jmp qword ptr [rip + returnInjectIDrop];"

        );
}

void  __attribute__((naked))InjectRecoveryPunish() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"//ANIM TABLE
        "push rbx;"//ANIM FROM TABLE
        "push rcx;"//ANIM TABLE SIZE
        "push rdx;"//PLAYER CURRENT ANIM
        "push rdi;"//COUNTER

        "cmp byte ptr [rip + izunaRecoveryPunish],0x00;"
        "jz exitRecoveryPunish;"

        "mov rax, qword ptr [rip + playerIdentAddress1];"
        "cmp rax,rbx;"
        "jne exitRecoveryPunish;"

        "lea rax, qword ptr [rip + izunaAnimIDs];"
        "mov rcx, [rip + izunaAnimIDsSize];"
        "dec rcx;"

        "xor rbx,rbx;"
        "xor rdx,rdx;"
        "xor rdi,rdi;"


        "izunaRecoveryPunishLoop:"
        "cmp rdi,rcx;"
        "ja exitRecoveryPunish;"
        "movzx rbx, word ptr [rax + rdi * 0x02];"
        "movzx rdx, word ptr [rsi +  0x16];"
        "cmp rbx,rdx;"
        "je punishRecovery;"
        "inc rdi;"
        "jmp izunaRecoveryPunishLoop;"

        "punishRecovery:"
        "mov word ptr [rsi + 0x04],0x0E0E;"
        
        "exitRecoveryPunish:"
        "pop rdi;"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "movzx eax, byte ptr [rbx + 0x1D];"
        "mov rcx, qword ptr [rip + RecoveryPunishLeaAddress];"
        "lea rcx, [rcx];"
        "or byte ptr [rax + rcx], 0x20;"
        "jmp qword ptr [rip + returnInjectRecoveryPunish];"

        );
}


void  __attribute__((naked))InjectDelimb3() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"//FS MOVETABLE
        "push rbx;"//FS MOVE
        "push rcx;"//COUNTER


        "lea rax, qword ptr [rip + fsMoveTable];"
        "xor rbx,rbx;"
        "xor rcx, rcx;"

        "fsDelimb3LoopStart:"
        "movzx rbx, word ptr [rax + rcx * 0x02];"
        "cmp rbx,r14;"
        "je setDelimb3;"
        "inc rcx;"
        "cmp rcx, 0x05;"
        "jle fsDelimb3LoopStart;"
        "jmp exitDelimb3;"


        "setDelimb3:"
        "movss xmm0, [rip + fsDelimbMulp];"

        "exitDelimb3:"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "movzx r8d, byte ptr [rdi + 0x09];"
        "mov rcx, [rsi + 0x48];"
        "shr r8d, 0x05;"
        "movss [rsp + 0x20],xmm0;"
        "jmp qword ptr [rip + returnInjectDelimb3];"

        );
}

void  __attribute__((naked))InjectEnemyDmgReduction() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"
        "push rbx;"
        "mov rax, qword ptr [rip + baseAddress];"
        "mov rbx, qword ptr [rip + activeDiffOffset];"

        "xorps xmm5,xmm5;"
        "xorps xmm10,xmm10;"
        "comiss xmm5,xmm2;"
        "je enemyDmgReductionExit;"

        //DIFF CHECK
        "movss xmm8, [rip + masterEnemyDmgReductionMulp]; "
        "cmp byte ptr [rax + rbx],0x04;"
        "je enemyDmgReductionStart;"

        "movss xmm8, [rip + mentorEnemyDmgReductionMulp]; "
        "cmp byte ptr [rax + rbx],0x03;"
        "je enemyDmgReductionStart;"

        "movss xmm8, [rip + warriorEnemyDmgReductionMulp]; "
        "cmp byte ptr [rax + rbx],0x02;"
        "je enemyDmgReductionStart;"

        "jmp enemyDmgReductionExit;"

        "enemyDmgReductionStart:"
        "movss xmm5,xmm2;"
        "divss xmm5,xmm8;"
        "comiss xmm5,xmm10;"
        "jb enemyDmgReductionExit;"
        "movss xmm1,xmm5;"
        "movss xmm2,xmm5;"

        "enemyDmgReductionExit:"
        "movd xmm4, eax;"
        "movzx eax, word ptr[r9 + 0x00009AC4];"
        "cvtdq2ps xmm4, xmm4;"
        "pop rbx;"
        "pop rax;"
        "jmp qword ptr [rip + returnEnemyDmgReduction];"
        );
}

void  __attribute__((naked))InjectEntDie() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rcx;"
        "xor rcx,rcx;"
        "mov [rip + entDied], cx;"
        "mov rcx, qword ptr [rip + baseAddress];"
        "cmp word ptr [rcx], 0x0000;"
        "jle codeentdie;"
        "movzx cx, byte ptr [rbx+0x18];"
        "mov [rip + entDied], cx;"
        "codeentdie:"
        "pop rcx;"
        "mov byte ptr [rbx+0x1A],-01;"
        "mov byte ptr [rax+0x00009B64],0x00;"
        "add rsp,0x58;"
        "jmp qword ptr [rip + returnInjectEntDie];"
        );
}

void  __attribute__((naked))InjectEntHitData() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rdx;"
        "lea rax, [r9 + r9 * 0x02];"
        "shl rax, 0x04;"
        "add rax, r10;"

        "lea rdx, qword ptr [rip + entHitInfo];"
        "mov [rdx], rax;"
        "mov [rdx+0x08], cx;"
        "mov [rdx+0x0A], r12b;"

        "pop rdx;"
        "cmp byte ptr[rax + 0x1A], 00;"
        "jmp qword ptr [rip + returnInjectEntHitData];"


        );
}

void  __attribute__((naked))InjectAIDodge() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rbx;"
        "push rcx;"
        "push rdx;"
       

        "cmp rax,0x05;"
        "jne exitAIDodge;"

        "mov rcx, qword ptr [rip + playerIdentAddress1];"
        "cmp rcx,rdi;"
        "jne exitAIDodge;"


        "xor rcx,rcx;"
        "movzx rdx, byte ptr [rip + randomNum];"
        "lea rbx, qword ptr [rip + entHitInfo];"
        "mov cx, word ptr [rbx + 0x08];"

        //FUTURE STUFF and make into better format, for now IF state and nasty 0 checks are ok for 2 ents lol

        "xor rbx,rbx;"
        "movzx rbx, byte ptr [rip + isNinjaDodgeBlockChance];"

        "cmp rbx,0x64;"
        "jz exitAIDodge;"

        "cmp cx,0x009C;"
        "je aiDodgeISNinja;"

        "movzx rbx, byte ptr [rip + isFiendNinjaDodgeBlockChance];"

        "cmp rbx,0x64;"
        "jz exitAIDodge;"

        "cmp cx,0x0070;"
        "je aiDodgeFiendISNinja;"

        "movzx rbx, byte ptr [rip + lizDodgeBlockChance];"

        "cmp rbx,0x64;"
        "jz exitAIDodge;"

        "cmp cx,0x0012;"
        "je aiDodgeLiz;"

        "jmp exitAIDodge;"


        "aiDodgeISNinja:"
        "cmp dx,bx;"
        "ja disableDodgeBlock;"
        "jmp exitAIDodge ;"

        "aiDodgeFiendISNinja:"
        "cmp dx,bx;"
        "ja disableDodgeBlock;"
        "jmp exitAIDodge ;"


        "aiDodgeLiz:"
        "cmp dx,bx;"
        "ja disableDodgeBlock;"
        "jmp exitAIDodge ;"



        "disableDodgeBlock:"
        "mov rax,0x0B;"


        "exitAIDodge:"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "mov rsi, [rsp + 0x58];"
        "mov rdi, [rsp + 0x60];"
        "mov r12, [rsp + 0x68];"
        "jmp qword ptr [rip + returnInjectAIDodge];"


        );
}

//HOW TO FIND
//add r12, rax - hook here
//mov[rsp + 20], rax
//mov eax, 0000000C
//cmp ax, r9w
void  __attribute__((naked))InjectTripleIS() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rcx;"
        "push rsi;"
        "push rdi;"
        "cmp byte ptr [rip + tripleIS],0x00;"
        "jz codeISTEST;"
        "cmp r11, 0x65535;"
        "jle codeISTEST;"
        "mov rsi, qword ptr [rip + baseAddress];"
        //"cmp byte ptr [rsi + 0x35C4218], 0x04;"
        //"jne codeISTEST;"
        "mov rcx,0x96;"
        "cmp dword ptr [r11+0x08], 0x0001019B;"
        "jne codeISTEST;"
        "lea rsi, qword ptr [rip + tripleISBytes];"
        "mov rdi,r11;"
        "rep movsb;"
        "codeISTEST:"
        "pop rdi;"
        "pop rsi;"
        "pop rcx;"
        "add r12,rax;"
        "mov [rsp+0x20],rax;"
        "mov eax,0x0000000C;"
        "cmp ax,r9w;"
        "jmp qword ptr [rip + returnInjectTripleIS];"


        );
}
//HOW TO FIND 
//mov r8d, eax
//mov edx, 00000046
//HOOK AT movss xmm3[,rax+0x18]
//IDK WTF THIS NASTY CODE IS LOL
void __attribute__((naked))InjectDelimb1() {

    __asm__ volatile(".intel_syntax noprefix;"
        //ORIGINAL CODE
        "push rcx;"
        "push rdx;"
        "xor rdx,rdx;"
        "mov rcx, qword ptr [rip+baseAddress];"
        "cmp r14,0xFFFF;"
        "je 2f;"
        "cmp r10,0x94;"
        "je setResistanceMax;"
        /*"cmp r14,0xC7C;"
         "je 3f;"
         "cmp r14,0xC7A;"
         "je 3f;"
         "cmp r14,0xD6E;"
         "je 3f;"
         "cmp r14,0xCA8;"
         "je 3f;"
         "cmp r14,0x7BB;"
         "je 3f;"*/
        "movss xmm15, [rip+resistance];"
        "comiss xmm15,[rax+0x18];"
        "jle setDelimb;"
        "jmp setDelimb;"
        "2:"
        "cmp r10,0x94;"
        "je setResistanceMax;"
        "movss xmm15, [rip+resistance];"
        "movss dword ptr [rax+0x18], xmm15;"
        "jmp 1f;"
        "setResistanceMax:"
        "movss xmm15, [rip + resistancemax];"
        "movss dword ptr [rax+0x18], xmm15;"
        "jmp 1f;"
        "3:"
        "movss xmm15, [rip+newVal3];"
        "movss dword ptr [rax+0x18], xmm15;"
        "cmp byte ptr [rcx+0x211E5CE],0x00;"
        "je 1f;"
        "movss xmm15, [rip+newVal4];"
        "movss dword ptr [rax+0x18], xmm15;"
        "jmp 1f;"
        "setDelimb:"//TODO DATASTRUCTURE AND LOOP INSTEAD

        "mov rdx,0x00000834;"
        "cmp r10,0x00000015;"
        "je setDelimbHigh;"

        "mov rdx,0x0000076C;"
        "cmp r10,0x00000011;"
        "je setDelimbHigh;"

        "cmp r14d,0x0C7A;"
        "je setDelimbFS;"

        "cmp r14d,0x0C7C;"
        "je setDelimbFS;"

        "cmp r14d,0x0D6E;"
        "je setDelimbFS;"

        "cmp r14d,0x0CA8;"
        "je setDelimbFS;"

        "cmp r14d,0x0D66;"
        "je setDelimbFS;"

        "cmp r14d,0x07BB;"
        "je setDelimbFS;"

        "xor rdx,rdx;"


        "movss xmm15, [rip+scytheDelimbMulp];"
        "cmp r10,0x00000012;"
        "je setDelimb2;"

        "movss xmm15, [rip+enmaDelimbMulp];"
        "cmp r10,0x00000021;"
        "je setDelimb2;"

        "movss xmm15, [rip+femaleDelimbMulp];"
        "cmp r12,0x000000DB;"
        "je setDelimb2;"

        "cmp r12,0x000000DC;"
        "je setDelimb2;"

        "cmp r12,0x000000DD;"
        "je setDelimb2;"

        "movss xmm15, [rip+newVal1];"
        //"movss xmm15, [rip+newVal3];"
        "setDelimb2:"
        "movss dword ptr [rax+0x18], xmm15;"
        "jmp 1f;"

        "setDelimbFS:"
        "movss xmm15, [rip + fsDelimbMulp];"
        "jmp setDelimb2;"

        "setDelimbHigh:"
        "movss xmm15, [rip+newVal1];"
        "cmp rdx,r14;"
        "jne setDelimb2;"
        "movss xmm15, [rip+highDelimbMulp];"
        "jmp setDelimb2;"

        "1:"
        "movss xmm3, [rax+0x18];"
        "mov rax,[rcx+0x1F35CF8];"
        "pop rdx;"
        "pop rcx;"
        "cmp byte ptr [rax+0x000003DE],0xFF;"
        "jmp qword ptr [rip+returnInjectDelimb1];"
        );
}

//void __attribute__((naked)) InjectDelimb2() {
//    __asm__ volatile(".intel_syntax noprefix;"
//        //ORIGINAL CODE
//       /* "movss xmm15, [rip+detectTest];"
//        "movss xmm14, [r9+0x01*0x4];"
//        "comiss xmm14, xmm15;"
//        "je detect1;"
//        "jmp 1f;"
//        "detect1:"*/
//        "cmp bp, 0x25E0;" //F3E0
//        "je 1f;"
//        "movss xmm15, [rip+detectTest2];"
//        "movss xmm14, [r9+0x04*0x4];"
//        "comiss xmm14, xmm15;"
//        "jle detect2;"
//        "addss xmm15, xmm15;"
//        "comiss xmm14,xmm15;"
//        "je detect2;"
//        "jmp 1f;"
//        "detect2:"
//        "movss xmm15, [rip+newVal2];"
//        "movss dword ptr [r9 + 0x00 * 0x8 + 0x10],xmm15;"
//        "movss xmm15, [rip+newVal1];"
//        "movss dword ptr [r9 + 0x00 * 0x8 + 0x14], xmm15;"
//        "movss dword ptr[r9 + 0x00 * 0x8 + 0x04], xmm15;"
//        "1:"
//        "movups xmmword ptr [r10], xmm0;"
//        "movsd qword ptr [r10+0x10], xmm1;"
//        "add rsp, 0x20;"
//        "jmp qword ptr [rip+returnInjectDelimb2]"
//        );
//}

void __attribute__((naked)) InjectDelimb2() {
    __asm__ volatile(".intel_syntax noprefix;"
        //ORIGINAL CODE
       /* "movss xmm15, [rip+detectTest];"
        "movss xmm14, [r9+0x01*0x4];"
        "comiss xmm14, xmm15;"
        "je detect1;"
        "jmp 1f;"
        "detect1:"*/
        "cmp si, 0x09C;" //F3E0
        "je canStartDelimb2;"
        "cmp si, 0x070;"
        "je canStartDelimb2;"
        "jmp 1f;"
        "canStartDelimb2:"
        "movss xmm15, [rip+newVal2];"
        "movss dword ptr [r9 + 0x00 * 0x8 + 0x10],xmm15;"
        "movss xmm15, [rip+newVal1];"
        "movss dword ptr [r9 + 0x00 * 0x8 + 0x14], xmm15;"
        "movss dword ptr[r9 + 0x00 * 0x8 + 0x04], xmm15;"
        "1:"
        "movups xmmword ptr [r10], xmm0;"
        "movsd qword ptr [r10+0x10], xmm1;"
        "add rsp, 0x20;"
        "jmp qword ptr [rip+returnInjectDelimb2]"
        );
}


//PLEASE FIX THIS NASTY ASS CODE FROM CT AND TURN TO DATA STRUCT
void  __attribute__((naked))InjectAnim() {

    __asm__ volatile(".intel_syntax noprefix;"

        "push rbx;"
        "push rdx;"
        "push rbp;"
        "push r8;"
        "mov rbp, qword ptr [rip + baseAddress];"
        "xor r8,r8;"
        "movzx r8, byte ptr [rip + randomNum];"

        /*  "cmp bx,0x7100;"
          "je isP;"*/
        "cmp bx,0x54F0;" //5300 equi
        "je isP;"

        "cmp cx,0x69;"
        "je guilThrow;"

        "cmp byte ptr [rbx+0x18],0x9D;"
        "je pGreyninja;"
        "cmp byte ptr [rbx+0x18],0x04;"
        "je pGreyninja;"
        "cmp byte ptr [rbx+0x18],0x38;"
        "je pGreyninja;"
        "cmp byte ptr [rbx+0x18],0x32;"
        "je pGaja;"
        "cmp byte ptr [rbx+0x18],0x9E;"
        "je pGaja;"
        "cmp byte ptr [rbx+0x18],0x24;"
        "je pZed;"
        "cmp byte ptr [rbx+0x18],0x27;"
        "je pFiendGenshin;"
        /* "cmp byte ptr [rbx+0x18],0x12;"
         "je pLiz;"*/
        "cmp byte ptr [rbx+0x18],0x23;"
        "je pRas;"
        "cmp byte ptr [rbx+0x18],0xA5;"
        "je pRas;"
       "cmp byte ptr [rbx+0x18],0x25;"
        "je pVolf;"
         "cmp byte ptr [rbx+0x18],0x20;"
         "je pAlexi;"
         "cmp byte ptr [rbx+0x18],0xB0;"
          "je pAlexi;"
        "cmp byte ptr [rbx+0x18],0xB1;"
        "je pWolf;"
        "cmp byte ptr [rbx+0x18],0x06;"
        "je pWolf;"
        "cmp byte ptr [rbx+0x18],0x9C;"
        "je isNinja;"
        "cmp byte ptr [rbx+0x18],0x08;"
        "je isNinja;"
        "cmp byte ptr [rbx+0x18],0x70;"
        "je fiendIS;"
        "cmp byte ptr [rbx+0x18],0x2F;"
        "je fiendGrey;"
        "cmp byte ptr [rbx+0x18],0x39;"
        "je waterDragon;"
        "cmp byte ptr [rbx+0x18],0x03;"
        "je pVanGelf;"
        "cmp byte ptr [rbx+0x18],0xA7;"
        "je pVanGelf;"
        "cmp byte ptr [rbx+0x18],0x75;"
        "je  pVanGelf;"

        "jmp exitAnim;"

        "guilThrow:"
       //"jmp exitAnim;"

        "xor rdx,rdx;"

        "lea rdx, qword ptr [rbx];"

        "test rdx,rdx;"
        "jz exitAnim;"

       /* "cmp byte ptr [rdx+0x5C8D],0x00;"
        "jnz exitAnim;"*/

        "mov rdx,rdi;"



        "cmp word ptr [rbp + 0x3380E30],0x09A5;"
        "jne exitAnim;"

        "mov di, 0x0E0;"
        "cmp byte ptr [rbx+0x18],0xF1;"
        "je exitAnim;"

        "mov di, 0x137;"
        "cmp byte ptr [rbx+0x18],0x2F;"
        "je exitAnim;"

        "mov di, 0x1FE;"
        "cmp byte ptr [rbx+0x18],0x9D;"
        "je exitAnim;"
        "cmp byte ptr [rbx+0x18],0x38;"
        "je exitAnim;"
        "cmp byte ptr [rbx+0x18],0x04;"
        "je exitAnim;"

        "mov di, 0x0DA;"
        "cmp byte ptr [rbx+0x18],0xA1;"
        "je exitAnim;"
        "cmp byte ptr [rbx+0x18],0x28;"
        "je exitAnim;"
        "cmp byte ptr [rbx+0x18],0x7C;"
        "je exitAnim;"

        "mov di, 0x12B;"
        "cmp byte ptr [rbx+0x18],0x9C;"
        "je exitAnim;"
        "cmp byte ptr [rbx+0x18],0x08;"
        "je exitAnim;"

        "mov di, 0x133;"
        "cmp byte ptr [rbx+0x18],0x70;"
        "je exitAnim;"

        "mov rdi,rdx;"
        "jmp exitAnim;"

        "isP:"
        /* "cmp di,0xA53;"
         "je gatlingAnimFix;"
         "cmp di,0xA4D;"
         "je gatlingAnimFix;"
         "cmp di,0xA1A;"
         "je gatlingAnimFix2;"
         "cmp di,0x46D;"
         "jne exitAnim;"
         "mov di,0x45D;"*/
         /* "cmp di,0xA4D;"
          ""*/
        "test rdi,rdi;"
        "je exitAnim;"

        "cmp byte ptr [rbx + 0x18], 0xDD;"
        "je isPMomiji;"


        "cmp byte ptr [rbp + 0x3380DE6],0x21;"
        "je isPFang;"

        "mov rdx,0x0C72;"
        "cmp word ptr [rbp + 0x3380E30],0x03E0;"
        "je pWindPath;"


        /* "cmp byte ptr [rbp + 0x319CBE6],0xCC;"
         "je isPDualSwords;"
         "cmp byte ptr [rbp + 0x319CBE6],0x13;"
         "je isPDualSwords;"*/

            "jmp exitAnim;"

        "cmp byte ptr [rbp + 0x3380DE8],0xA0;"
        "jne exitAnim;"
        "cmp di,0xA1B;"
        "je gatlingAnimFix;"
        "cmp di,0xA4E;"
        "je gatlingAnimFix2;"
        "cmp di,0xA53;"
        "je gatlingAnimFix2;"
        "cmp di,0xA5B;"
        "je gatlingAnimFix2;"

        "jmp exitAnim;"

        "pWindPath:"
        "cmp dx,di;"
        "jne exitAnim;"
        "mov di,0x0C87;"
        "jmp exitAnim;"

        //"isPDualSwords:"
        //"cmp di,0xD71;"
        //"jne exitAnim;"
        //"mov di,0xD6E;"
        //"mov cx,0x0B;"
        //"jmp exitAnim;"

        "isPFang:"
        "cmp di,0xCB3;"
        "jne exitAnim;"
        "mov di,0xCED;"
        "jmp exitAnim;"

        "gatlingAnimFix:"
        "test rcx,rcx;"
        "jnz exitAnim;"
        "mov di,0xA1A;"
        "jmp exitAnim;"

        "gatlingAnimFix2:"
        "mov rdi,0xA1B;"
        "jmp exitAnim;"

        "isPMomiji:"
        "cmp rdi,0x13B;"
        "jne exitAnim;"
        "mov rdi,0x135;"
        "jmp exitAnim;"

        "waterDragon:"
        /* "cmp byte ptr [rbp + 0x35C4218], 0x04;"
         "jne exitAnim;"*/
        //"cmp word ptr [rax + 0x09AC6],0x028A;"
        //"jle waterDragonOT;"
        ///*"cmp byte ptr [rip+canWaterDragonAttacks],0x01;"
        //"je waterDragonAttacks;"*/
        //"jmp exitAnim;"

        "waterDragonAttacks:"
        "cmp byte ptr [rip + waterDragonBattleStart],0x02;"
        "jl waterDragonPreStart;"
        "cmp cx,0xA8;"
        "jne exitAnim;"
        "test rdi,rdi;"
        "jne exitAnim;"
        "cmp byte ptr [rbp + 0x3380F03],0x04;"
        "jnae exitAnim;"
        "xor rdi,rdi;"
        "inc byte ptr [rip+canWaterDragonAttacks];"
        "cmp byte ptr [rip + canWaterDragonAttacks],0x06;"
        "jle exitAnim;"
        "mov byte ptr [rip + canWaterDragonAttacks],0x00;"
        "mov rdi,0x04;"//MOVE AROUND
        "cmp r8, 0x019;"
        "jle exitAnim;"
        "xor rdi,rdi;"

           

        "mov rdi,0x015;"//WHIP
        "cmp r8, 0x032;"
        "jle exitAnim;"

        "mov di,0x01D;"
        "cmp r8, 0x06C;"
        "jle exitAnim;"

        "xor rdi,rdi;"
        "jmp exitAnim;"

       /* "cmp byte ptr [rip + waterDragonDived],0x00;"
        "jnz waterDragonDiveReset;"
       
        "mov byte ptr [rip + waterDragonDived],0x01;"
        "jmp exitAnim;"*/

        "waterDragonDiveReset:"
        "mov byte ptr [rip + waterDragonDived],0x00;"
        "mov di,0x04;"
        "mov cx,0x6F;"
        "jmp exitAnim;"

        "waterDragonAttackReset:"
        "mov byte ptr [rip + canWaterDragonAttacks],0x00;"
        "xor rdi,rdi;"
        "jmp exitAnim;"

        "waterDragonPreStart:"
        /*"cmp di,0x01F;"
        "jne exitAnim;"*/
        "inc byte ptr [rip + waterDragonBattleStart];"
        "mov di,0x01B;"
        "jmp exitAnim;"

        "waterDragonOT:"
        "push rax;"
        "mov rax, qword ptr [rbx];"
        "cmp rax,r15;"
        "jl waterDragonOTFail;"

        /*"cmp byte ptr [rbp + 0x3380F03],0x04;"
        "jnae exitAnim;"*/
        "cmp word ptr [rax + 0x09AC6],0x028A;"
        "jae waterDragonOTFail;"
        "cmp byte ptr [rip+canWaterDragonOT],0x00;"
        "jnz waterDragonOTFail;"
        "mov byte ptr [rip+canWaterDragonOT],0x01;"
        "mov di,0x25;"
        "pop rax;"
        "jmp exitAnimRefacWhen;"

        "waterDragonOTFail:"
        "pop rax;"
        "jmp exitAnimRefacWhen;"
        //PORTED HORRIBLY STRAIGHT FROM CT LOL
        "pWolf:"
        "cmp di,0x3A;"
        "jne exitAnim;"
        "mov di,0x39;"
        "jmp exitAnim;"

        "pVanGelf:"
        "cmp di,0x00CD;"
        "je pVanGelfJumpGrab;"
        "cmp di,0x00CA;"
        "je pVanGelfNormalGrab;"
        

        "cmp r8,0x28;"
        "jae exitAnim;"
        "cmp di,0x0040;"
        "je pVanGelfNormalGrab;"

        "cmp r8,0x28;"
        "jae exitAnim;"
        "cmp di,0x0060;"
        "je pVanGelfNormalGrab;"

        "jmp exitAnim;"

        "pVanGelfJumpGrab:"
        "cmp byte ptr [rip + vangelfGrabSpeed],0x00;"
        "jnz exitAnim;"
        "mov di,0x0064;"
        "jmp exitAnim;"

        "pVanGelfNormalGrab:"
        "cmp byte ptr [rip + vangelfGrabSpeed],0x00;"
        "jnz exitAnim;"
        "mov di,0x0068;"
        "jmp exitAnim;"

        "pGreyninja:"

        "cmp di,0x0141;"
        "je pGreyGrabTwo;"

        "cmp di,0x04A9;"
        "je pGreyGrabTwo;"

        "cmp di,0x170;"
        "je pGreyGrabOne;"

        "cmp di,0x04A8;"
        "je pGreyGrabOne;"

        "cmp di,0x012F;"
        "je pGreyDoubleKick;"
        "jmp exitAnim;"

        "pGreyDoubleKick:"
        "cmp r8,0x19;"
        "jae exitAnim;"
        "mov di,0x0140;"
        "jmp exitAnim;"

        "pGreyGrabOne:"
        "mov di,0x0170;"
        "cmp byte ptr [rip+greyNinjaGrabSpeed],0x00;"
        "jz exitAnim;"
        "mov di,0x04A8;"
        "jmp exitAnim;"

        "pGreyGrabTwo:"
        "mov di,0x0141;"
        "cmp byte ptr [rip+greyNinjaGrabSpeed],0x00;"
        "jz exitAnim;"
        "mov di,0x04A9;"
        "jmp exitAnim;"

        "pRas:"
        "cmp di,0x3D;"
        "je tempWindFix;"
        "cmp di,0x35;"
        "je rasGrabCancel;"
        "cmp di,0x31;"
        "je rasGrabCancel;"
        "cmp di,0x40;"
        "jne exitAnim;"
        "mov di,0x3F;"
        "jmp exitAnim;"

        "tempWindFix:"
        "mov di,0x3E;"
        "jmp exitAnim;"

        "rasGrabCancel:"
        "cmp r8,0x28;"
        "jae exitAnim;"
        "mov di,0x3F;"
        "jmp exitAnim;"

        "pZed:"
        "cmp di,0x25;"
        "je zedGrabCheck;"
        "cmp di,0x24;"
        "je zedGrabCheck;"
        "jmp exitAnim;"

        "zedGrabCheck:"
        "mov di,0x24;"
        "cmp byte ptr [rip+zedGrabSpeed],0x00;"
        "jz exitAnim;"
        "mov di,0x25;"
        "jmp exitAnim;"

        "pLiz:"
        "cmp di,0x43;"
        "je lizGrabCheck;"
        "cmp di,0x42;"
        "je lizGrabCheck;"
        "jmp exitAnim;"

        "lizGrabCheck:"
        "mov di,0x42;"
        "cmp byte ptr [rip+lizGrabSpeedTail],0x00;"
        "jz exitAnim;"
        "mov di,0x43;"
        "jmp exitAnim;"

        "pFiendGenshin:"
        "cmp di,0x3F;"
        "jne exitAnim;"
        "mov di,0x3E;"
        "jmp exitAnim;"

        "pVolf:"
        "cmp di,0x1B;"
        "jne exitAnim;"
        "cmp r8,0x32;"
        "jae exitAnim;"
        "mov di,0x22;"
        "jmp exitAnim;"

        "pGaja:"
        "cmp di,0x4D;"
        "jne exitAnim;"
        "mov di,0x4C;"
        "jmp exitAnim;"

        "pAlexi:"
        ////QUIT
        //"jmp exitAnim;"
        //"cmp di,0x50;"
        //"je pAlexiGrab;"
        "cmp di,0x30;"
        "je pAlexiSpin;"
        "cmp di,0x3A;"
        "je pAlexiAirCombo;"
        "jmp exitAnim;"

        "pAlexiAirCombo:"
        "cmp r8,0x19;"
        "jae exitAnim;"
        "mov di,0x4E;"
        "jmp exitAnim;"


        "pAlexiSpin:"
        "mov di,0x34;"
        "jmp exitAnim;"

        "pAlexiGrab:"
        "mov di,0x4F;"
        "cmp byte ptr [rbp + 0x2294FA8],0x0F;"
        "jae exitAnim;"
        //AIR GROUND COMBO
        "mov di,0x60;"
        "jmp exitAnim;"

        "fiendIS:"
        "mov rbx,rdi;"
        "cmp di,0x26;"
        "je applyAnimFix;"
        "cmp di,0x22;"
        "je applyAnimFix;"

        "cmp rdi,0x9A;"
        "je fiendisPExplode;"

        "cmp rdi,0x86;"
        "je fiendisPExplode;"

        "cmp rdi,0x80;"
        "je fiendisPExplode;"

        "cmp rdi,0x82;"
        "je fiendisPExplode;"

        "cmp rdi,0x7B;"
        "je fiendisPExplode;"


        "cmp rdi,0xA0;"
        "mov rdi,0x9F;"
        "je exitAnim;"
        "mov rdi,rbx;"

        "cmp rdi,0x9D;"
        "mov rdi,0x9C;"
        "je exitAnim;"
        "mov rdi,rbx;"

        "cmp rdi,0xA6;"
        "mov rdi,0xA5;"
        "je exitAnim;"
        "mov rdi,rbx;"

        "jmp exitAnim;"

        "fiendisPExplode:"
        "cmp r8,0x28;"
        "jae exitAnim;"
        "mov rdi,0x9C;"
        "jmp exitAnim;"

        "fiendGrey:"
        "mov rbx,rdi;"
        "cmp rdi,0x9E;"
        "mov rdi,0xA9;"
        "je fiendpGreyExplode;"
        "mov rdi,rbx;"


        "cmp rdi,0x99;"
        "mov rdi,0x98;"
        "je exitAnim;"
        "mov rdi,rbx;"


        "cmp rdi,0x9C;"
        "mov rdi,0x9B;"
        "je exitAnim;"
        "mov rdi,rbx;"

        "cmp rdi,0x88;"
        "je fiendpGreyExplode;"

        "cmp rdi,0x86;"
        "je fiendpGreyExplode;"

        "cmp rdi,0x82;"
        "je fiendpGreyExplode;"



        "jmp exitAnim;"

        "fiendpGreyExplode:"
        "cmp r8,0x42;"
        "jae exitAnim;"
        "mov rdi,0x9B;"
        "jmp exitAnim;"

        "isNinja:"
        "mov rbx,rdi;"
        "cmp di,0x26;"
        "je applyAnimFix;"
        "cmp di,0x22;"
        "je applyAnimFix2;"
        "cmp rdi,0x9E;"
        "je isNinjaGrabCheck;"
        "mov rdi,rbx;"
        "jmp exitAnim;"

        "isNinjaGrabCheck:"
        "mov rdi,0x9D;"
        "cmp byte ptr [rip + isNinjaGrabSpeed],0x00;"
        "jz exitAnim;"
        "mov rdi,rbx;"
        "jmp exitAnim;"

        "guilthrow:"
        "mov rbx,rdi;"


        "applyAnimFix:"
        "mov di,0x1C;"
        "jmp exitAnim;"
        "applyAnimFix2:"
        "mov di,0x1B;"

        "exitAnim:"
        "pop r8;"
        "pop rbp;"
        "pop rdx;"
        "pop rbx;"
        "movzx eax,al;"
        "mov rdx, qword ptr [rip + baseAddress];"
        "lea rdx, qword ptr [rdx + 0x1F37270];"
        "mov rdx,[rdx+rax*0x08];"
        "cmp word ptr [rbx + 0x18],0x0039;"
        "je waterDragonOT;"

        "jmp exitAnimRefacWhen;"

        "exitAnimRefacWhen:"
        "cmp rdx,-01;"
        "jmp qword ptr [rip + returnInjectAnim];"
        );
}




void  __attribute__((naked))InjectFreeCam() {

    __asm__ volatile(".intel_syntax noprefix;"

        "cmp byte ptr [rip+isFreeCamAll],0x00;"
        "jnz freeCam;"

        "cmp byte ptr [rip+isFreeCamIzunaOnly],0x00;"
        "jz freeCamExit;"

        "cmp r8w, 0x10C;"
        "je freeCam;"
        "cmp r8w,0x15;"
        "je freeCam;"
        "cmp r8w,0xB6;"
        "je freeCam;"

        "freeCamExit:"
        "imul rcx,rax,0x000016F0;"
        "add rcx,[rdi+0x00000EC8];"
        "jmp qword ptr [rip + returnInjectFreeCam];"

        "freeCam:"
        "jmp qword ptr [rip + returnInjectFreeCamCall];"





        );
}


void  __attribute__((naked))InjectInventoryCCNew() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"
        "push rcx;"
        "mov rax, qword ptr [rip+baseAddress];"
        "cmp byte ptr [rip+inventoryCCNew],0x00;"
        "jnz exitInjectInventoryCCNew;"
        //FEMALES
       /* "cmp byte ptr [rax+0x35C421A],0x37;"
        "je exitInjectInventoryCCNew;"
        "cmp byte ptr [rax+0x35C421A],0x36;"
        "je exitInjectInventoryCCNew;"
        "cmp byte ptr [rax+0x35C421A],0x35;"
        "je exitInjectInventoryCCNew;"*/
        "xor rcx,rcx;"
        "mov rcx,0x87000005;"
        "mov [rbx+0x11C],rcx;"
        "mov rcx,0x87000001;"
        "mov [rbx+0x12C],rcx;"
        "mov byte ptr [rbx+0x90],0x23;"
        "mov rcx, 0x0000000100000022;"
        "mov [rbx+0x120],rcx;"
       /* "mov rcx, 0x00000001000000A0;"
        "mov [rbx+0xB0],rcx;"*/
        /*  "mov byte ptr [rbx+0x13B],0x01;"*/
        "mov byte ptr [rip+inventoryCCNew],0x01;"

        "exitInjectInventoryCCNew:"
        "pop rcx;"
        "pop rax;"
        "mov r8d,r12d;"
        "mov edi, [rbx+0x08];"
        "movzx edx,si;"
        "add rbx,0x0C;"
        "mov [rsp+0x20],r12d;"
        "jmp qword ptr [rip+returnInjectInventoryCCNew];"


        );
}






void __attribute__((naked)) InjectSound() {
    __asm__ volatile (
        ".intel_syntax noprefix;"
        "push rsi;"
        "mov rsi, qword ptr [rip + baseAddress];"
        "cmp r8, 0x2;"
        "jne 2f;"
        "cmp byte ptr [rsi + 0x222BEC8],0x10;"
        "je CHP14SoundTrack;"
        "cmp r9, 0x3b;"//MAIN MENU
        "je 1f;"
        "cmp r9, 0x45;"
        "je 0f;"
        "jmp 2f;"
        "0:"
        "movzx r9, byte ptr [rip+ch1HeroTrack];"
        //"mov r9,0x3D;"
        "jmp 2f;"
        "CHP14SoundTrack:"
        "cmp r9,0x3B;"
        "je codesound22;"
        "cmp r9,0x2F;"
        "je codesound22;"
        "cmp r9,0x4E;"
        "je codesound23;"
        "jmp 2f;"
        "codesound22:"
        "movzx r9, byte ptr [rip+ch14HeroTrack];"
        //"mov r9,0x4D;"
        "jmp 2f;"
        "codesound23:"
        "mov r9,0x55;"
        "jmp 2f;"
        "1:"
        "movzx r9, byte ptr [rip+mainMenuTrack];"
        //"mov r9, 0x3E;"
        "2:"
        "mov [rdx],r8d;"
        "xor ebp,ebp;"
        "mov [rdx+04],r9d;"
        "mov rbx,rdx;"
        "mov rax, [rcx+0x130];"
        "pop rsi;"
        "jmp qword ptr [rip + returnInjectSound];"
        "3:"
        );
}

void __attribute__((naked)) InjectFOV() {

    __asm(".intel_syntax noprefix;"
    ".intel_syntax noprefix;"
        "movdqu [rdi+0x20],xmm0;"
        "mov eax,[rbx+0x30];"

       /* "cmp eax,0x3F5F66F5;"
        "jle exitFOV;"*/


        "movd xmm14,[rip+fovValue];"
        "movd xmm15,eax;"
        "addss xmm15,xmm14;"
        "movd eax,xmm15;"

              

        "exitFOV:"
        "mov [rdi+0x30],eax;"
        "mov eax, [rbx+0x34];"
        "mov [rdi+0x34],eax;"
        "jmp QWORD PTR [rip + returnInjectFOV];"
        );
}

void  __attribute__((naked))InjectDelimbFiends() {

    __asm__ volatile(".intel_syntax noprefix;"
        "mov [r14],rax;"
        "movzx r12d, word ptr [rax];"
        "add rax,0x02;"
        "mov [r14],rax;"
        "movzx esi, word ptr [rax];"

        "push rax;"//BASE ADDRESS
        "push rbx;"//HALFCUT ANIM ADDRESS
        "push rcx;"//COUNTER
        "push rdx;"//HALF CUT ANIM
        "push rdi;"//player anim
        //ONLY SWAP HEAD FOR HALF

       



        "mov rax, qword ptr [rip+baseAddress];"
        "lea rbx, qword ptr [rip+lycanHalfCutTable];"
        "cmp r8,rax;"
        "jle exitDelimbFiends;"

        //VERIFY IF LYCAN
        "cmp byte ptr [r8],0x06;"
        "je isLycanC;"
        "cmp byte ptr [r8],0xB1;"
        "je isLycanC;"
        "cmp byte ptr [r8],0x0C;"
        "je isLycanC;"
        "jmp exitDelimbFiends;"

        "isLycanC:"
        "xor rcx,rcx;"
        "xor rdx,rdx;"
        "xor rdi,rdi;"

        "delimbFiendsStart:"
        "mov dx, word ptr [rbx+rcx*0x02];"
        "mov di, word ptr [rax+0x3380E30];"
        "test rdi,rdi;"
        "jz exitDelimbFiends;"
        "test rdx,rdx;"
        "jz exitDelimbFiends;"
        "cmp dx,di;"
        "je setHalfCutFiends;"
        "inc rcx;"
        "cmp rcx,0x03;"
        "jle delimbFiendsStart;"
        "jmp exitDelimbFiends;"

        "setHalfCutFiends:"
        "cmp di,0x4A2;"
        "je clawsCheck;"

        "cmp di,0x49E;"
        "je botaCheck;"

        "cmp si,0x00;"
        "je setHalfCutFiend;"

        "jmp exitDelimbFiends;"

        "clawsCheck:"
        "cmp si,0x02;"
        "jne exitDelimbFiends;"
        "jmp setHalfCutFiend;"

        "botaCheck:"
        "cmp si,0x03;"
        "jne exitDelimbFiends;"
        "jmp setHalfCutFiend;"

        "setHalfCutFiend:"
        "mov rsi,0x05;"

        "exitDelimbFiends:"
        "pop rdi;"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "jmp qword ptr [rip+returnInjectDelimbFiends];"




        );
}

void __attribute__((naked)) InjectCLoop() {

    __asm__ volatile(".intel_syntax noprefix;"
        //ORIGINAL CODE
        "mov rcx,[rbx+0x10];"
        "mov rdx,r10;"
        "call qword ptr [rbx+0x08];"
        //INJECTED CODE
        "push rbx;"
        "cmp byte ptr [rip+canSpawn], 0x01;"
        "je spawnme;"
        "cmp byte ptr [rip+canspawn2], 0x01;"
        "je spawnme;"
        "jmp codec;"
        "spawnme:"
        "mov eax,0x02;"
        "codec:"
        "pop rbx;"
        "inc eax;"
        "cmp eax,0x07;"
        "jmp qword ptr [rip + returnInjectCLoop];"

        );

}

void  __attribute__((naked))InjectDisableSpawns() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"
        "mov rax, qword ptr [rip+baseAddress];"
        "lea r8, qword ptr [rax+0x6C49AF0];"
        "xor ebx,ebx;"
        "lea rdx, qword ptr [rax+0x2155E90];"
        "pop rax;"
        "mov r9d,ebx;"
        "cmp byte ptr [rip+cDeleteEnemy],0x01;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "jne exitDeleteSpawn;"
        "mov rax, qword ptr [rip+baseAddress];"
        "add rax,0x174B63F;"
        "jmp rax;"
        "exitDeleteSpawn:"
        "jmp qword ptr [rip + returnInjectDisableSpawns]; "
        //"call qword ptr [rdi+0X15d9560];"

        );
}

void  __attribute__((naked))InjectHalfCutHuman() {

    __asm__ volatile(".intel_syntax noprefix;"
        "push rax;"//BASE ADDRESS
        "push rbx;"//FS ID TABLE
        "push rcx;"//COUNTER
        "push rdx;"//ARRAY FS ID
        "push r14;"
        "push r15;"

        "cmp rdi,0x01;"
        "jne exitHalfCutHuman;"

        "cmp word ptr [r8],0x0014;"
        "je exitHalfCutHuman;"
        "cmp word ptr [r8],0x00F1;"
        "je exitHalfCutHuman;"

        //50% of headcut or halfcut
        "xor r15,r15;"
        "movzx r15, byte ptr [rip + randomNum];"
        "cmp r15,0x32;"
        "jle exitHalfCutHuman;"

        "mov rax, qword ptr [rip+baseAddress];"
        "lea rbx, qword ptr [rip+fsMoveTable];"

        "xor rcx,rcx;"
        "xor rdx,rdx;"
        "xor r14,r14;"

        "movzx r14, word ptr [rax + 0x3380E30];"

        //SCYTHE WALL THROW
        "cmp r14,0x0D33;"
        "je halfCutMatch;"

        //DS UPWARD HEAD DELIMB OT
        "cmp r14,0x04BC;"
        "je halfCutMatch;"

        //DS KICK HEAD DELIMB OT
        "cmp r14,0x04C2;"
        "je halfCutMatch;"

        "halfCutLoopStart:"
        "mov dx, word ptr [rbx+rcx*0x02];"
        "test rdx,rdx;"
        "jz exitHalfCutHuman;"
        "cmp rdx,r14;"
        "je halfCutMatch;"
        "inc rcx;"
        "cmp rcx,0x0B;"
        "jle halfCutLoopStart;"
        "jmp exitHalfCutHuman;"

        "halfCutMatch:"
        "xor rdi,rdi;"

        "exitHalfCutHuman:"
        "pop r15;"
        "pop r14;"
        "pop rdx;"
        "pop rcx;"
        "pop rbx;"
        "pop rax;"
        "lea rax, [r11 + 0x02];"
        "mov [r14], rax;"
        "movzx r15d, word ptr [rax];"
        "add rax,0x02;"
        "jmp qword ptr [rip + returnInjectHalfCutHuman];"

        );
}

#pragma endregion GENERAL_HOOKS




#pragma region MASTER_NINJA
void  __attribute__((naked))InjectCoords() {

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
        "cmp byte ptr [rax + rbx],0x04;"
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
        "jmp exitInjectCoords;"

        //CAVE (NOT NEEDED
       /* "cmp DWORD PTR[rdx], 0x0101;"
        "jne exitInjectCoords;"
        "movaps xmm10, [rcx+0x10];"
        "jmp setCoords;"*/

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
        "cmp byte ptr [rip + randomNum],0x21;"
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


void  __attribute__((naked))InjectEventTrigger() {

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
        "cmp byte ptr [rsi + rbx],0x04;"
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
        //CH4
        "mov byte ptr [rip + chp4MuesumBtlCounter], 0x00;"
        //CH6
        "mov byte ptr [rip + chp6RebirthBtlCounter],0x00;"
        "mov byte ptr [rip + chp6SecondSaveBtlCounter],0x00;"
        "mov byte ptr [rip + chp6WindmillBtlCounter],0x00;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "add rsi, 0x02;"
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

void  __attribute__((naked))InjectC() {

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
        "cmp byte ptr [r9 + rbx],0x04;"
        "jne exitInjectC;"
        
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "xor r8,r8;"

        //LEVEL CHECK
        "mov rsi, qword ptr [rip + activeChapterAddress];"

        //ENEMIES ALIVE ADDRESS (SOME CHAPTERS SEEM TO USE DIFFERENT ADDRESSES (USE THIS AND ONLY ADDRESS 2 IF REQUIRED)
        "mov r10, qword ptr [rip + enemyAliveAddress];"

        //GOOD FOR CHAPTER 2 AND CHAPTER 1 RASETSU
        "mov r12, qword ptr [rip + enemyAliveAddress2];"

        "xor r8,r8;"

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

        //CHAPTER 7
        "lea rbx, qword ptr [rip + masterninjaCH7OriginalSpawnTriggerOffsets];"
        "cmp byte ptr [rsi],0x0B;"
        "je chapter7Master;"

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
        "ja spawnGreyNinja;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "mov byte ptr [rip+canSpawn],0x01;"
        "inc byte ptr [rip+cBattleRespawnCount];"
        "mov dword ptr [r8],0x0101;"
        "jmp spawnGreyninjabow;"

        //FIRST BATTLE AFTER THIRD SAVE
        "setEnemyCHP01SAKURA:"
        "inc byte ptr [rip+cManualSpawnResetCounter];"
        "mov byte ptr [rip+canSpawn],0x01;"
        "cmp byte ptr [rip+cManualSpawnResetCounter],0x02;"
        "jle spawnMage;"
        "cmp byte ptr [rip+cManualSpawnResetCounter],0x07;"
        "jle spawnISNinja;"
        "mov byte ptr [rip+cManualSpawnResetCounter],0x00;"
        "jmp spawnISNinja;"

        //BATTLE RIGHT BEFORE BUDDAH
        "setEnemyCHP01BUDDAHBEFORE:"
        "inc byte ptr [rip+cBattleRespawnCount3];"
        "cmp byte ptr [rip+cBattleRespawnCount3],0x03;"
        "jle spawnISNinja;"
        "jmp spawnGreyNinja;"

        //2ND LAST SAVE IS NINJA (HALLWAY OG2 RESTORED SPAWN)
        "setEnemyCHP01HALLWAYOG2:"
        "mov byte ptr [rip+cDeleteEnemy],0x01;"
        "mov dword ptr [r8 + 0x02 * 0x04],0x0F0F;"
        "mov byte ptr [rip+cDeleteEnemy],0x00;"
        "mov byte ptr [rip+canSpawn],0x01;"
        "inc byte ptr [rip+cBattleRespawnCount4];"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x05;"
        "ja spawnISNinja;"
        "mov dword ptr [r8 + 0x02 * 0x04],0x0101;"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x01;"
        "jle spawnMage;"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x03;"
        "jle spawnGreyNinja;"
        "cmp byte ptr [rip+cBattleRespawnCount4],0x05;"
            "jle spawnISNinja;"
            "jmp spawnISNinja;"

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


            "stairCase:"
            "inc byte ptr [rip + cBattleRespawnCount];"
            "cmp byte ptr [rip + cBattleRespawnCount],0x01;"
            "jle spawnISNinja;"
            "cmp byte ptr [rip + cBattleRespawnCount],0x04;"
            "jle spawnGreyNinja;"
            "mov byte ptr [rip + cBattleRespawnCount],0x00;"
            "jmp spawnGreyNinja;"

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
            "jmp spawnISNinja;"

            "setEnemyCHP202:"
            "mov byte ptr [rip+cDeleteEnemy],0x01;"
            "mov dword ptr [r8 + 0x02 * 0x04],0x0F0F;"
            "mov r11, qword ptr [rbx + 0x18];"
            "cmp byte ptr [rip+cBattleRespawnCount7],0x03;"
            "ja disableEnemyEvent;"
            "inc byte ptr [rip + cBattleRespawnCount7];"
            "mov byte ptr [rip+cDeleteEnemy],0x00;"
            "mov byte ptr [rip+canSpawn],0x01;"
            "mov dword ptr [r8 + 0x02 * 0x04],0x0101;"
            "cmp byte ptr [rip + cBattleRespawnCount7],0x02;"
            "jle spawnGreyNinja;"
            "jmp spawnISNinja;"

            "setEnemyCHP203:"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x01;"
            "mov DWORD PTR [r8 + 0x04 * 0x04], 0x0F0F;"
            "mov r11, qword ptr [rbx + 0x20];"
            "cmp BYTE PTR [rip + cBattleRespawnCount8], 0x1F;"
            "ja disableEnemyEvent;"
            "mov DWORD PTR [r8 + 0x04 * 0x04], 0x0101;"
            "cmp BYTE PTR [r10], 0x06;"
            "ja exitInjectC;"
            "cmp BYTE PTR [r12], 0x07;"
            "ja exitInjectC;"
            "inc BYTE PTR [rip + cBattleRespawnCount8];"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
            "jmp spawnISNinja;"






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
            "mov DWORD PTR [r8], 0x0F0F;"
            "cmp BYTE PTR [rip + cBattleRespawnCount], 0x1F;"
            "jae exitInjectC;"
            "inc BYTE PTR [rip + cBattleRespawnCount];"
            "mov BYTE PTR [rip + cDeleteEnemy], 0x00;"
            "mov DWORD PTR [r8], 0x0101;"
            "jmp spawnVangelf;"

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

            //AFTER ENMA PICKUP, NEXT ROOM WITH TORCH (9C)
            "mov rdi,[rbx + 0x30];"
            "add rdi,r9;"
            "cmp rcx,rdi;"
            "je setEnemyCHP404;"



            "jmp exitInjectC;"

            "setEnemyCHP401:"
            "mov byte ptr [rdx + 0x14], 0x00;"
            "mov r11, qword ptr [rbx + 0x10];"
            "lea rsi, qword ptr [rip + chp4MuesumSpawn];"
            "mov rcx, [rip + chp4MuesumSpawnSize];"
            "lea r15, qword ptr [rip + chp4MuesumBtlCounter];"
            "movzx r13, byte ptr [rip + chp4MuesumBtlMaxSpawnCap];"
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

                //A FISH SPAWN THAT WATER DRAGON CALLS
                "mov rdi,[rbx + 0x30];"
                "add rdi,r9;"
                "cmp rcx,rdi;"
                "je setEnemyCHP604;"


                "mov rdi,[rbx + 0x48];"
                "add rdi,r9;"
                "cmp rcx,rdi;"
                "je setEnemyCHP605;"

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
                "jle spawnGajaRed;"
                "mov byte ptr [rip+canspawn2],0x00;"
                "jmp spawnMage;"

                //IS REBIRTH
                "setEnemyCHP602:"
                "cmp dword ptr [r8 + 0x02 * 0x04],0x0101;"
                "je setEnemyCHP602a;"
                "cmp dword ptr [r8],0x0101;"
                "jne exitInjectC;"
                //BATTLE COMPLETED MARKER
                "mov r11, qword ptr [rbx + 0x18];"
                "lea rsi, qword ptr [rip + chp6RebirthSpawn];"
                "mov rcx, [rip + chp6RebirthSpawnSize];"
                "lea r15, qword ptr [rip + chp6RebirthBtlCounter];"
                "movzx r13, byte ptr [rip + chp6RebirthBtlMaxSpawnCap];"
                "jmp spawnEnemyOnlyWaveAliveOne;"
                
                //WINDMILL
                "setEnemyCHP602a:"
                "mov byte ptr [rdx + 0x14], 0x09;"
                //BATTLE TRACKER OFFSET
                "mov r12,0x02;"
                "mov r11, qword ptr [rbx + 0x20];"
                "lea rsi, qword ptr [rip + chp6WindmillSpawn];"
                "mov rcx, [rip + chp6WindmillSpawnSize];"
                "lea r15, qword ptr [rip + chp6WindmillBtlCounter];"
                "movzx r13, byte ptr [rip + chp6WindmillBtlMaxSpawnCap];"
                "jmp spawnEnemyOnlyWaveAliveOneFixed;"

                "setEnemyCHP603:"
                "lea rsi, qword ptr [rip + chp6SecondSaveAmbushSpawn];"
                "mov rcx, [rip + chp6SecondSaveAmbushSpawnSize];"
                "lea r15, qword ptr [rip + chp6SecondSaveBtlCounter];"
                "jmp spawnEnemyOnlyNoWave;"

                "setEnemyCHP604:"
                "mov byte ptr [rip + canSwapCoords],0x01;"
                "cmp byte ptr [r12],0x03;"
                "ja exitInjectC;"
                "mov rdi, [rbx + 0x38];"
                "add rdi,r9;"
                "mov byte ptr [rdi],0x01;"
                "mov rdi, [rbx + 0x40];"
                "add rdi,r9;"
                "mov byte ptr [rdi],0x01;"
                "jmp exitInjectC;"

                "setEnemyCHP605:"
                "cmp byte ptr [rip + canSwapCoords],0x00;"
                "jz spawnGajaRed;"
                /*"cmp byte ptr [r10],0x02;"
                "ja exitInjectC;"*/
                "mov byte ptr [rip + cDeleteEnemy],0x01;"
                "cmp byte ptr [r12],0x03;"
                "ja exitInjectC;"
                "mov byte ptr [rip + cDeleteEnemy],0x00;"
                "mov byte ptr [rip + canSwapCoords],0x00;"
                "mov word ptr [rdx + 0x064],0x45A0;"
                "jmp spawnVangelfGoldFly;"

              
           
              


#pragma endregion

#pragma region CHAPTER_7_MASTER_SPAWNS
                "chapter7Master:"

                //FIRST STEPS LEADING TO WATER AREA
                "mov rdi,[rbx];"
                "add rdi,r9;"
                "cmp rcx,rdi;"
                "je setEnemyCHP701;"

                "mov rdi,[rbx + 0x08];"
                "add rdi,r9;"
                "cmp rcx,rdi;"
                "je setEnemyCHP702;"

                "mov rdi,[rbx + 0x10];"
                "add rdi,r9;"
                "cmp rcx,rdi;"
                "je setEnemyCHP703;"


                "jmp exitInjectC;"

                "setEnemyCHP701:"
                "mov byte ptr [rip+canspawn2],0x01;"
                "inc byte ptr [rip+cBattleRespawnCount];"
                "cmp byte ptr [rip+cBattleRespawnCount],0x04;"
                "jle spawnISNinja;"
                "cmp byte ptr [rip+cBattleRespawnCount],0x05;"
                "jle spawnMage;"
                "mov byte ptr [rip+canspawn2],0x00;"
                "jmp spawnGajaRed;"

                "setEnemyCHP702:"
                "mov byte ptr [rip+canspawn2],0x01;"
                "inc byte ptr [rip+cBattleRespawnCount2];"
                "cmp byte ptr [rip+cBattleRespawnCount2],0x03;"
                "jle spawnImps;"
                "cmp byte ptr [rip+cBattleRespawnCount2],0x06;"
                "jle spawnISNinja;"
                "mov byte ptr [rip+canspawn2],0x00;"
                "jmp spawnGajaRed;"

                "setEnemyCHP703:"
                "mov byte ptr [rip+canspawn2],0x01;"
                "inc byte ptr [rip+cBattleRespawnCount3];"
                "cmp byte ptr [rip+cBattleRespawnCount3],0x02;"
                "jle spawnGajaRed;"
                "cmp byte ptr [rip+cBattleRespawnCount3],0x03;"
                "jle spawnMage;"
                "cmp byte ptr [rip+cBattleRespawnCount3],0x06;"
                "jle spawnImps;"
                "cmp byte ptr [rip+cBattleRespawnCount3],0x09;"
                "jle spawnISNinja;"
                "mov byte ptr [rip+canspawn2],0x00;"
                "jmp spawnGajaRed;"




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
                "cmp BYTE PTR [rip + cBattleRespawnCount], 0x0F;"
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
                "cmp byte ptr [rip+cBattleRespawnCount9],0x02;"
                "jle spawnISNinjaN;"
                "cmp byte ptr [rip+cBattleRespawnCount9],0x05;"
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

                    /*"cmp bx,0x2560;"
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

        "spawnGreenNinja:"
        "mov byte ptr [rdx+0x04],0x04;"
        "mov byte ptr [rdx+0x1C],0x03;"
        "mov byte ptr[rdx + 0x2C], 0xFF;"
        "mov byte ptr[rdx + 0x30], 0xFF;"
        "mov byte ptr[rdx + 0x31], 0xFF;"
        "mov byte ptr[rdx + 0x38], 0xFF;"
        "mov byte ptr[rdx + 0x3C], 0xFF;"
        "mov byte ptr[rdx + 0x3D], 0xFF;"
        "mov r14,0x04;"
        "jmp exitInjectC;"

        "spawnISNinja:"
        "mov r14d,0x9C;"
        "mov byte ptr [rdx + 0x04], 0x9C;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"

        "spawnBrownNinja:"
        "mov r14d,0x08;"
        "mov byte ptr [rdx + 0x04], 0x08;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "jmp exitInjectC;"



        "spawnISNinjaN:"
        "mov r14d,0x9C;"
        "mov byte ptr [rdx + 0x04], 0x9C;"
        "mov byte ptr [rdx+0x1C], 0x1C;"
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

        "spawnImps:"
        "mov r14d,0xF1;"
        "mov byte ptr [rdx + 0x04], 0xF1;"
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

        "spawnVangelfGreenFly:"
        "mov r14d,0x75;"
        "mov byte ptr [rdx + 0x04], 0x75;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x14], 0x09;"
        "jmp exitInjectC;"

        "spawnVangelfGoldFly:"
        "mov r14d,0xA7;"
        "mov byte ptr [rdx + 0x04], 0xA7;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x14], 0x09;"
        "jmp exitInjectC;"

        "spawnVangelfJump:"
        "mov r14d,0x03;"
        "mov byte ptr [rdx + 0x04], 0x03;"
        "mov byte ptr [rdx+0x1C], 0x03;"
        "mov byte ptr [rdx+0x14], 0x01;"
        "jmp exitInjectC;"

        "spawnFlyingRobot:"
        "mov byte ptr [rdx+0x04],0x1D;"
        "mov byte ptr [rdx+0x1C],0x03;"
        "mov r14,0x1D;"
        "jmp exitInjectC;"

        "spawnGajaRed:"
        "mov r14d,0x9E;"
        "mov byte ptr [rdx + 0x04], 0x9E;"
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

        "spawnEnemyOnlyWaveAliveOneBothEnemyCountCheck:"
        "cmp dword ptr [r8], 0x0101;"
        "jne exitInjectC;"
        "dec rcx;"
        "mov byte ptr [rip + cDeleteEnemy], 0x01;"
        //ACTIVE ALIVE ENEMIES CHECK
        "cmp byte ptr [r10], r13b;"
        "ja exitInjectC;"
        "inc r13;"
        "cmp byte ptr [r12], r13b;"
        "ja exitInjectC;"
        "dec r13;"
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





