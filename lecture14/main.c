#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("USAGE: page_size levels 64/32\n");
        exit(1);
    }
    int page_size = strtol(argv[1], 0, 10);
    int levels = strtol(argv[2], 0, 10);
    int arch_bits = strtol(argv[3], 0, 10);
    int page_bits = __builtin_ctz(page_size);
    if (levels < 0 || levels > 5 ||
        (arch_bits != 32 && arch_bits != 64)) {
        printf("Invalid params: levels %d arch_bits %d\n", levels,
                         arch_bits);
        exit(2);
    }

    if (page_size != (1 << page_bits)) {
        printf("Invalid page_size %d, did you mean %d\n",
                page_size, (1 << page_bits));
        exit(2);
    }

    printf("%d page_size is %d bits\n", page_size, page_bits);

    unsigned long long addr = (unsigned long long)main;

    unsigned long long VPN = addr >> page_bits;
    unsigned long long offset = addr & (page_size-1);
    printf("VPN %llx offset %llx\n", VPN, offset);
    int index_bits = __builtin_ctz(page_size/(arch_bits/8));
    for (int i = 0; i < levels; i++) {
        int entry_index = (VPN >> (i*index_bits)) & ((1 << index_bits) - 1);
        printf("P%d entry_index = %x\n", i+1, entry_index);
        //VPN >>= index_bits;
    }
}
