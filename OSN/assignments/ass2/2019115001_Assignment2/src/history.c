#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_HIST 20
static char *hist[MAX_HIST];
static int  hist_count = 0;

// Load up to MAX_HIST entries from ~/.history into memory
void history_init(void) {
    const char *home = getenv("HOME");
    if (!home) return;

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/.history", home);

    FILE *f = fopen(path, "r");
    if (!f) return;

    char line[1024];
    while (hist_count < MAX_HIST && fgets(line, sizeof(line), f)) {
        size_t len = strlen(line);
        if (len && line[len - 1] == '\n')
            line[len - 1] = '\0';
        hist[hist_count++] = strdup(line);
    }
    fclose(f);
}

// Record a command: append to memory and to ~/.history
void history_record(const char *cmd) {
    if (!cmd || !*cmd) return;

    char buf[1024];
    strncpy(buf, cmd, sizeof(buf));
    buf[sizeof(buf)-1] = '\0';
    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n')
        buf[len - 1] = '\0';

    if (hist_count < MAX_HIST) {
        hist[hist_count++] = strdup(buf);
    } else {
        free(hist[0]);
        memmove(hist, hist+1, (MAX_HIST-1)*sizeof(char *));
        hist[MAX_HIST-1] = strdup(buf);
    }

    const char *home = getenv("HOME");
    if (!home) return;
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/.history", home);
    FILE *f = fopen(path, "a");
    if (!f) return;
    fprintf(f, "%s\n", buf);
    fclose(f);
}

// Show last n commands (or all if n <= 0 or n > hist_count)
void history_show(int n) {
    int start = 0;
    if (n > 0 && n < hist_count)
        start = hist_count - n;
    for (int i = start; i < hist_count; ++i)
        printf("%s\n", hist[i]);
}

// Up-arrow navigation stub (not implemented)
char *history_navigate(void) {
    return NULL;
}
