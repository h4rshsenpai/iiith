#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    printf("parent before fork: pid=%d\n", getpid());
    fflush(stdout);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("child: pid=%d parent=%d\n", getpid(), getppid());
        return 0;
    }

    int status = 0;
    waitpid(pid, &status, 0);
    printf("parent after wait: child=%d status=%d\n", pid, status);
    return 0;
}
