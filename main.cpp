#include <iostream>
#include "AntiObfusHunter.hpp"

int main() {
    VerifyIntegrity();
    LEAVE_DECOY_FOR_DUMPER();

    std::cout << "[+] Protected string 1: " << ANTI_DUMP_STRING("This string is completely invisible to your dumper.") << std::endl;
    std::cout << "[+] Protected string 2: " << ANTI_DUMP_STRING("ObfusHunter is blind. StringDumper is deaf. SigRemover is trapped.") << std::endl;
    std::cout << "[+] Execution completed successfully. All protections active." << std::endl;

    return 0;
}
