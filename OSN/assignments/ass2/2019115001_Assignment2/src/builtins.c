#include "builtins.h"
#include "history.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>

int handle_builtin(char **argv) {
    // cd
    if (!strcmp(argv[0], "cd")) {
        const char *path = argv[1] ? argv[1] : getenv("HOME");
        if (chdir(path) < 0) perror("cd");
        return 1;
    }
    // pwd
    if (!strcmp(argv[0], "pwd")) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd))) puts(cwd);
        else perror("pwd");
        return 1;
    }
    // echo
    if (!strcmp(argv[0], "echo")) {
        for (int i = 1; argv[i]; i++)
            printf("%s%s", argv[i], argv[i+1] ? " " : "\n");
        return 1;
    }
    if (!strcmp(argv[0], "repeat")) {
        if (!argv[1] || !argv[2]) {
            fprintf(stderr, "repeat: usage: repeat <count> <command> [args]");
            return 1;
        }
        int times = atoi(argv[1]);
        for (int i = 0; i < times; i++) {
            // Build sub-argv starting at argv[2]
            char *subargv[64];
            int j = 0;
            while (argv[j+2] && j < 62) {
                subargv[j] = argv[j+2];
                j++;
            }
            subargv[j] = NULL;
            // If sub-command is builtin, execute internally
            if (handle_builtin(subargv)) {
                continue;
            }
            pid_t pid = fork();
            if (pid < 0) {
                perror("repeat: fork");
            } else if (pid == 0) {
                execvp(subargv[0], subargv);
                perror("repeat: execvp");
                exit(1);
            } else {
                waitpid(pid, NULL, 0);
            }
        }
        return 1;
    }
    // pinfo
    if (!strcmp(argv[0], "pinfo")) {
        pid_t pid = argv[1] ? atoi(argv[1]) : getpid();
        char status_path[PATH_MAX], exe_link[PATH_MAX];
        snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);
        FILE *f = fopen(status_path, "r");
        char line[256], state[32] = "?", vmsize[32] = "?";
        if (f) {
            while (fgets(line, sizeof(line), f)) {
                if (!strncmp(line, "State:", 6))
                    sscanf(line, "State:\t%31s", state);
                if (!strncmp(line, "VmSize:", 7))
                    sscanf(line, "VmSize:\t%31s", vmsize);
            }
            fclose(f);
        }
        printf("pid -- %d\nProcess Status -- %s\nMemory -- %s\n", pid, state, vmsize);
        char exe_path[PATH_MAX];
        snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);
        ssize_t len = readlink(exe_path, exe_link, sizeof(exe_link)-1);
        if (len != -1) {
            exe_link[len] = '\0';
            printf("Executable Path -- %s\n", exe_link);
        }
        return 1;
    }
    // history 
    if (!strcmp(argv[0], "history")) {
       // if user passed a number, show only that many; otherwise show all
    if (argv[1]) {
        int n = atoi(argv[1]);
        history_show(n);
    } else {
        history_show(0);
    }
    return 1;
    }

    return 0;
}