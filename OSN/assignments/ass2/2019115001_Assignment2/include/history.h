#ifndef HISTORY_H
#define HISTORY_H

// Initialize history (load .history), record a command, show history list
void history_init(void);
void history_record(const char *line);
void history_show(int n);
// Handle up‑arrow navigation (returns chosen line or NULL)
char *history_navigate(void);

#endif // HISTORY_H