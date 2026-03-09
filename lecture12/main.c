#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int page_bits = strtol(argv[1], 0, 10);
    long long addr = (long long)main;
    printf("main is at address %p\n", main);
    long long VPN = addr >> page_bits;
    int mask = (1 << page_bits) - 1;
    int offset = addr & (mask);
    printf("   VPN = %llx offset=%x\n", VPN, offset);
}
