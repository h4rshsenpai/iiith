#include "executor.h"
#include <unistd.h>
#include <wait.h>
#include<stdlib.h>
#include <stdio.h>

void execute_command(char **argv, int bg) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
    } else if (pid == 0) {
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    } else {
        if (bg) printf("[%d]\n", pid);
        else waitpid(pid, NULL, 0);
    }
}