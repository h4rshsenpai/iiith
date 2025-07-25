#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <limits.h>

void display_prompt(void) {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    const char *home = getenv("HOME");
    if (home && strncmp(cwd, home, strlen(home)) == 0) {
        printf("<%s@%s:~%s>",
            getpwuid(getuid())->pw_name,
            getenv("HOSTNAME"),
            cwd + strlen(home));
    } else {
        printf("<%s@%s:%s>",
            getpwuid(getuid())->pw_name,
            getenv("HOSTNAME"),
            cwd);
    }
    printf(" ");
    fflush(stdout);
}