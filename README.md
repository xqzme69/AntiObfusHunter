# AntiObfusHunter

A direct counter-measure repository against `ObfusHunter`, `ObfusHide-StringDumper`, and `ObfusFake-Signatures-Remover`. 

## How it works

1. **Anti-ObfusHunter**: The `mutate_obfus.py` script acts as a polymorphic engine for `obfus.h` itself. It randomly mutates the inline assembly instructions (e.g. converting `xor eax, eax` to `sub eax, eax`) and section names at compile-time. Static YARA/byte scanners like `ObfusHunter` become completely blind as the signatures shift every build.

2. **Anti-StringDumper**: The `ObfusHide-StringDumper` statically scans for sequence of `mov` instructions pushing hidden strings to the stack. `AntiObfusHunter.hpp` provides `ANTI_DUMP_STRING`, which evaluates mathematically at runtime via a template lambda instead of doing raw memory writes. The dumper sees nothing. I also leave a decoy string for the dumper: `"Nice try hACKCASCAC"`. 

3. **Anti-SigRemover**: The `ObfusFake-Signatures-Remover` statically zeroes out known fake section markers like `.enigma1`. I intentionally lay down a `.enigma1` section, and compute a checksum of it at runtime. If the remover touches my file, the checksum fails and the program terminates immediately, trapping the remover tool.

## Build

```cmd
build.bat
```

Run `main.exe` and test his tools against it!
