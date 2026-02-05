#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
void main() {
    int a = 3;
    printf("%d\n",  a);
    pid_t pid = fork();
    if (pid == 0) {
        printf("I'm the child\n");
        printf("Goodbye\n");
        exit(0);
    }
    a += 2;
    printf("%p\n", &a);
    printf("Waiting on the child %d\n", pid);
    sleep(50);
    pid_t finished_pid = wait(NULL);
    printf("Pid %d finished\n", finished_pid);
}
