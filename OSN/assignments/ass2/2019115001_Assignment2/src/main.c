#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "prompt.h"
#include "parser.h"
#include "executor.h"
#include "builtins.h"
#include "history.h"

// Handler for background child termination
void sigchld_handler(int sig) {
    (void)sig;
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        char buf[128];
        int len = snprintf(buf, sizeof(buf), "\n[%d] exited with code %d\n",
                           pid, WIFEXITED(status) ? WEXITSTATUS(status) : status);
        write(STDOUT_FILENO, buf, len);
        display_prompt(); // redisplay prompt after message
    }
}

int main(void) {
    // Ensure PATH is set so execvp can locate external commands
    if (!getenv("PATH")) {
        setenv("PATH", "/bin:/usr/bin", 1);
    }
    // Install SIGCHLD handler for bg jobs
    signal(SIGCHLD, sigchld_handler);
    history_init();

    char *line = NULL;
    size_t len = 0;

    while (1) {
        display_prompt();
        if (getline(&line, &len, stdin) < 0) {
            printf("\n");
            break;  // EOF
        }
        history_record(line);

        char *saveptr;
        for (char *cmd = strtok_r(line, ";", &saveptr);
             cmd;
             cmd = strtok_r(NULL, ";", &saveptr)) {

            int bg = 0;
            char **argv = parse_command(cmd, &bg);
            if (!argv || !argv[0]) { free_args(argv); continue; }

            if (!handle_builtin(argv)) {
                execute_command(argv, bg);
            }
            free_args(argv);
        }
    }
    free(line);
    return 0;
}