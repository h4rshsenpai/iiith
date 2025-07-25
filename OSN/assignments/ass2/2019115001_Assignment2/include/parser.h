#ifndef PARSER_H
#define PARSER_H

// Split input line by ';', handle '&', build argv array
char **parse_command(char *line, int *is_background);
// Free argv array
void free_args(char **argv);

#endif // PARSER_H