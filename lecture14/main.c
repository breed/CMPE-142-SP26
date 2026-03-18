#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t generate_random(int cr3) {
    uint64_t r = rand();
    uint64_t top = r << 63;
    r >>=1;
    uint64_t bottom = cr3 ? 2 : 0x67;
    return ((r % 0xFFFFF) << 12) | top | bottom;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("USAGE: page_size_kb levels 64/32\n");
        exit(1);
    }
    int page_size = strtol(argv[1], 0, 10)*1024;
    int levels = strtol(argv[2], 0, 10);
    int arch_bits = strtol(argv[3], 0, 10);
    int page_bits = __builtin_ctz(page_size);
    if (levels < 0 || levels > 5 ||
        (arch_bits != 32 && arch_bits != 64)) {
        printf("Invalid params: levels %d arch_bits %d\n", levels,
                         arch_bits);
        exit(2);
    }

    if ((page_size & (page_size - 1)) != 0) {
        printf("Invalid page_size %d, did you mean %d\n",
                page_size, (1 << page_bits));
        exit(2);
    }

    int entry_bits = __builtin_ctz(page_size / (arch_bits/8));

    printf("%d page_size is %d bits entry_bits %d\n",
        page_size, page_bits, entry_bits);

    uint64_t addr = (unsigned long long)main;
    uint64_t VPN = addr >> page_bits;
    uint64_t offset = addr & ((1 << page_bits)-1);

    uint64_t cr3 = generate_random(1);

    printf("CR3 = %lx addr %lx VPN %lx offset %lx\n", cr3, addr, VPN, offset);

    uint64_t paddr = cr3 & (~0xfff);

    for (int i = 0; i < levels; ++i) {
        int entry_index = (VPN >> i * entry_bits) &
                  ((1<<entry_bits) -1);
        printf("P%d %x entry_index\n", i+1, entry_index);
        uint64_t boffset = entry_index * (arch_bits/8);
        printf("P%d %lx entry byte offset\n", i+1, boffset);
        uint64_t naddr = generate_random(0);
        printf("P%d read %lx and found %lx\n", i+1, paddr + boffset, naddr);
        paddr = naddr & (~0x8000000000000FFFULL);
    }
}
