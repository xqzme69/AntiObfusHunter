import re
import random
import sys

def randomize_hex(match):
    return hex(random.randint(1, 255)).replace('0x', '0x').upper()

def mutate_obfus(input_path, output_path):
    with open(input_path, 'r', encoding='utf-8') as f:
        content = f.read()

    def repl_xor(m):
        opts = [
            f"subl %{m.group(1)}, %{m.group(1)}",
            f"movl $0, %{m.group(1)}"
        ]
        return random.choice(opts)

    content = re.sub(r'xorl\s+%([a-z]+),\s+%\1', repl_xor, content)
    content = re.sub(r'\.byte\s+0x[0-9a-fA-F]{2}', lambda m: f".byte 0x{random.randint(0, 255):02X}", content)

    sections = [
        "vmp0", "vmp1", "vmp2", "enigma1", "enigma2", "obfh", 
        "winlice", "petite", "rlp", "dsstext", "logicoma", "adr", "have", "30cm",
        "PETETRIS", "alien", "pwdprot", "arch", "vlizer", "__wibu00"
    ]
    
    for sec in sections:
        content = content.replace(f'"{sec}"', f'"rnd{random.randint(10,99)}"')
        content = content.replace(f'".{sec}"', f'".rnd{random.randint(10,99)}"')

    content = content.replace('.byte 0x0f, 0x31', '.byte 0x0f; .byte 0x31')
    content = content.replace('.byte 0x0f, 0xc7, 0xf8', '.byte 0x0f; .byte 0xc7; .byte 0xf8')

    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(content)
        
    print(f"[+] Mutated {input_path} -> {output_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: mutate_obfus.py <in> <out>")
        sys.exit(1)
    mutate_obfus(sys.argv[1], sys.argv[2])
