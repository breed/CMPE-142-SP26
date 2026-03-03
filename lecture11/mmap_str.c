/*
 * pass a file on the command line to map into memory and modify using
 * memory operations.
 *
 * a quick way to setup a file full of '\0': dd if=/dev/zero of=data count=1024
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDWR);
    char *buffer = mmap(NULL, 65536, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    while(1) {
        printf("%s\n", buffer);
        sleep(2);
        strcat(buffer, "*");
    }
}
