#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *trim(char *s) {
    while (*s && isspace((unsigned char)*s)) s++;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

char **parse_command(char *line, int *is_background) {
    char *cmd = trim(line);
    int bg = 0;
    size_t n = strlen(cmd);
    if (n && cmd[n-1] == '&') {
        bg = 1;
        cmd[--n] = '\0';
        trim(cmd);
    }
    *is_background = bg;

    char **argv = calloc(64, sizeof(char*));
    int argc = 0;
    for (char *tok = strtok(cmd, " \t\n"); tok; tok = strtok(NULL, " \t\n"))
        argv[argc++] = tok;
    argv[argc] = NULL;
    return argv;
}

void free_args(char **argv) {
    free(argv);
}