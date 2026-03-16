#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int page_bits = strtol(argv[1], 0, 10);
    printf("main = %p\n", main);
    long long addr = (long long)main;
    long long VPN = addr >> page_bits;
    int offset = addr & ((1<<page_bits)-1);
    printf("VPN = %llx offset = %x\n", VPN, offset);
}
