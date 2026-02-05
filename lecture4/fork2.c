#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
void main() {
    int a = 3;
    printf("%d\n",  a);
    pid_t pid = fork();
    if (pid == 0) {
        // this is the child
        int rc = execlp("/bin/ech", "/bin/echo", "child says ***hello****", NULL);
        printf("Child exit execlp returned %d\n", rc);
        exit(0);
    }
    printf("I am the parent\n");
    printf("I'll wait for child %d to finish\n", pid);
    pid_t finished_pid = wait(NULL);
    printf("I started pid %d and pid %d finished\n", pid, finished_pid);
    printf("Parent exit\n");
}
