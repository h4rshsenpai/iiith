#ifndef EXECUTOR_H
#define EXECUTOR_H

// Execute argv; if bg==1, run background and print pid, else wait
void execute_command(char **argv, int bg);

#endif // EXECUTOR_H