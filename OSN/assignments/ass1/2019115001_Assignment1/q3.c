/*
 * q3.c: Check permissions of Assignment directory, output_file_1, and output_file_2
 * Uses system calls only; no printf/scanf; use stat and write.
 *
 * Functions used:
 * - stat(const char *path, struct stat *buf): retrieve file/directory status (mode, etc). Header: <sys/stat.h>
 * - S_ISDIR(mode): macro to test if mode indicates a directory. Header: <sys/stat.h>
 * - write(int fd, const void *buf, size_t count): write raw bytes to file descriptor. Header: <unistd.h>
 * - strlen(const char *s): compute length of C-string. Header: <string.h>
 * - strrchr(const char *s, int c): find last occurrence of a character in a string. Header: <string.h>
 * - snprintf(char *str, size_t size, const char *format, ...): safe formatted string print. Header: <stdio.h>
 * - sprintf(char *str, const char *format, ...): formatted string print (unsafe). Header: <stdio.h>
 * - perror(const char *s): print descriptive error message based on errno. Header: <stdio.h>
 * - PATH_MAX: maximum length of a filesystem path. Header: <limits.h>
 * - EXIT_SUCCESS, EXIT_FAILURE: standard exit status macros. Header: <stdlib.h>
 *
 * Logic:
 * 1. Parse command-line argument: input file path.
 * 2. Extract filename and build paths:
 *    - dirpath = "Assignment"
 *    - file1 = "Assignment/1_<filename>"
 *    - file2 = "Assignment/2_<filename>"
 * 3. stat() on dirpath:
 *    - If exists and is directory: print "Directory is created: Yes"
 *      else: print "Directory is created: No"
 * 4. For each target (file1, file2, dirpath):
 *    a. stat() to get st_mode.
 *    b. Check and print permissions for user, group, and others (r, w, x).
 * 5. Exit.
 */

#include <sys/stat.h>   // stat, S_ISDIR, permission macros
#include <sys/types.h>
#include <unistd.h>     // write
#include <string.h>     // strlen, strrchr
#include <stdio.h>      // snprintf, sprintf
#include <stdlib.h>     // EXIT_SUCCESS, EXIT_FAILURE
#include <errno.h>      // errno, perror
#include <limits.h>     // PATH_MAX

int check_and_print(const char *path, struct stat *st) {
    if (stat(path, st) < 0) {
        perror(path);
        return -1;
    }
    char buf[128];
    // User permissions
    sprintf(buf, "User has read permission on %s: %s\n", path,
            (st->st_mode & S_IRUSR) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    sprintf(buf, "User has write permission on %s: %s\n", path,
            (st->st_mode & S_IWUSR) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    sprintf(buf, "User has execute permission on %s: %s\n", path,
            (st->st_mode & S_IXUSR) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    // Group permissions
    sprintf(buf, "Group has read permission on %s: %s\n", path,
            (st->st_mode & S_IRGRP) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    sprintf(buf, "Group has write permission on %s: %s\n", path,
            (st->st_mode & S_IWGRP) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    sprintf(buf, "Group has execute permission on %s: %s\n", path,
            (st->st_mode & S_IXGRP) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    // Others permissions
    sprintf(buf, "Others has read permission on %s: %s\n", path,
            (st->st_mode & S_IROTH) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    sprintf(buf, "Others has write permission on %s: %s\n", path,
            (st->st_mode & S_IWOTH) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    sprintf(buf, "Others has execute permission on %s: %s\n", path,
            (st->st_mode & S_IXOTH) ? "Yes" : "No");
    write(STDOUT_FILENO, buf, strlen(buf));
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        const char *msg = "Usage: ./q3 <input_file_path>\n";
        write(STDERR_FILENO, msg, strlen(msg));
        return EXIT_FAILURE;
    }
    const char *inpath = argv[1];
    const char *fname = strrchr(inpath, '/');
    fname = (fname ? fname + 1 : inpath);

    char dirpath[PATH_MAX];
    snprintf(dirpath, sizeof(dirpath), "Assignment");

    char file1[PATH_MAX];
    snprintf(file1, sizeof(file1), "Assignment/1_%s", fname);

    char file2[PATH_MAX];
    snprintf(file2, sizeof(file2), "Assignment/2_%s", fname);

    struct stat st;
    // Check directory existence
    if (stat(dirpath, &st) == 0 && S_ISDIR(st.st_mode)) {
        const char *msg = "Directory is created: Yes\n";
        write(STDOUT_FILENO, msg, strlen(msg));
    } else {
        const char *msg = "Directory is created: No\n";
        write(STDOUT_FILENO, msg, strlen(msg));
    }
    // Check permissions for file1, file2, and directory
    check_and_print(file1, &st);
    check_and_print(file2, &st);
    check_and_print(dirpath, &st);

    return EXIT_SUCCESS;
}
