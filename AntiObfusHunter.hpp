#pragma once

#include <windows.h>
#include <iostream>
#include "obfus_mutated.h"

#pragma section(".enigma1", read, write)
__declspec(allocate(".enigma1")) 
volatile unsigned char g_fake_enigma_sig[] = {
    0x45, 0x6e, 0x69, 0x67, 0x6d, 0x61, 0x20, 0x70, 
    0x72, 0x6f, 0x74, 0x65, 0x63, 0x74, 0x6f, 0x72, 
    0x20, 0x76, 0x01
};

#define EXPECTED_ENIGMA_SUM 0x6EA

inline void VerifyIntegrity() {
    int sum = 0;
    for (int i = 0; i < sizeof(g_fake_enigma_sig); i++) {
        sum += g_fake_enigma_sig[i];
    }
    if (sum != EXPECTED_ENIGMA_SUM) {
        std::cout << "\n[!] TAMPERING DETECTED!" << std::endl;
        std::cout << "[!] Nice try hACKCASCAC, your Remover tool just broke the application." << std::endl;
        ExitProcess(1);
    }
}

template <size_t N>
struct AntiDumpStr {
    char data[N];
    __forceinline AntiDumpStr(const char* s, int seed) {
        for (size_t i = 0; i < N - 1; i++) {
            int mixed = (int)s[i] ^ (seed + i);
            data[i] = (char)(mixed ^ (seed + i));
        }
        data[N - 1] = '\0';
    }
    __forceinline char* get() { return data; }
};

#define ANTI_DUMP_STRING(str) (AntiDumpStr<sizeof(str)>(str, __LINE__ * 1337).get())

#define LEAVE_DECOY_FOR_DUMPER() \
    volatile char decoy[] = {'N','N','i','c','e',' ','t','r','y',' ','h','A','C','K','C','A','S','C','A','C','\0'}; \
    (void)decoy;
