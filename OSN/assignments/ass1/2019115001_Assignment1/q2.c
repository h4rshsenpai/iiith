/*
 * q2.c: Reverse a specific part of the file (1-based) into Assignment/2_<filename>
 * Uses system calls only; prints progress percentage overwritten on console.
 *
 * Functions used:
 * - open(const char *path, int flags): open file for reading. Header: <fcntl.h>
 * - lseek(int fd, off_t offset, int whence): move file pointer. Header: <unistd.h>
 * - mkdir(const char *path, mode_t mode): create directory. Header: <sys/stat.h>
 * - read(int fd, void *buf, size_t count): read bytes from fd. Header: <unistd.h>
 * - write(int fd, const void *buf, size_t count): write bytes to fd. Header: <unistd.h>
 * - close(int fd): close an open file descriptor. Header: <unistd.h>
 * - strlen(const char *s): length of a C‑string. Header: <string.h>
 * - strrchr(const char *s, int c): find last occurrence of c in s. Header: <string.h>
 * - atoi(const char *nptr): convert string to int. Header: <stdlib.h>
 * - snprintf(char *str, size_t size, const char *fmt, ...): safe formatting. Header: <stdio.h>
 * - sprintf(char *str, const char *fmt, ...): simple formatting. Header: <stdio.h>
 * - perror(const char *s): print error message from errno. Header: <stdio.h>
 * - EXIT_SUCCESS, EXIT_FAILURE: standard exit codes. Header: <stdlib.h>
 * - PATH_MAX: maximum path length constant. Header: <limits.h>
 *
 * Logic:
 * 1. Parse args: input file, num_parts, part_to_reverse.
 * 2. Open file; get total size via lseek.
 * 3. Compute block_size = total/num_parts, and start offset.
 * 4. Ensure “Assignment” directory exists.
 * 5. Build output path “Assignment/2_<filename>” and open it.
 * 6. Loop: for remaining bytes in that block, seek to correct offset, read chunk, reverse buffer, write it, print percentage.
 * 7. Clean up and exit.
 */

#include <fcntl.h>      // open
#include <unistd.h>     // read, write, lseek, close
#include <sys/stat.h>   // mkdir, permission macros
#include <string.h>     // strlen, strrchr
#include <stdlib.h>     // EXIT_SUCCESS, EXIT_FAILURE, atoi
#include <stdio.h>      // snprintf, sprintf, perror
#include <errno.h>      // errno
#include <limits.h>     // PATH_MAX

#define BUF_SIZE 8192  // 8 KB buffer

int main(int argc, char *argv[]) {
    if (argc != 4) {
        const char *msg = "Usage: ./q2 <input_file> <num_parts> <part_to_reverse>\n";
        write(STDERR_FILENO, msg, strlen(msg));
        return EXIT_FAILURE;
    }

    const char *inpath = argv[1];
    int num_parts = atoi(argv[2]), part_idx = atoi(argv[3]);
    if (num_parts <= 0 || part_idx < 1 || part_idx > num_parts) {
        const char *m = "Invalid parts or part index\n";
        write(STDERR_FILENO, m, strlen(m));
        return EXIT_FAILURE;
    }

    const char *fname = strrchr(inpath, '/');
    fname = fname ? fname + 1 : inpath;

    int infd = open(inpath, O_RDONLY);
    if (infd < 0) { perror("open input"); return EXIT_FAILURE; }

    off_t total = lseek(infd, 0, SEEK_END);
    if (total < 0) { perror("lseek total"); close(infd); return EXIT_FAILURE; }

    off_t block = total / num_parts;
    off_t start = block * (part_idx - 1), remaining = block;

    if (mkdir("Assignment", S_IRWXU) < 0 && errno != EEXIST) {
        perror("mkdir"); close(infd); return EXIT_FAILURE;
    }

    char outpath[PATH_MAX];
    snprintf(outpath, sizeof(outpath), "Assignment/2_%s", fname);

    int outfd = open(outpath, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    if (outfd < 0) { perror("open output"); close(infd); return EXIT_FAILURE; }

    char buf[BUF_SIZE];
    off_t processed = 0;

    while (remaining > 0) {
        ssize_t chunk = remaining > BUF_SIZE ? BUF_SIZE : remaining;
        off_t offset = start + (remaining - chunk);
        if (lseek(infd, offset, SEEK_SET) < 0) { perror("lseek read"); break; }
        ssize_t nr = read(infd, buf, chunk);
        if (nr < 0) { perror("read"); break; }
        for (ssize_t i = 0; i < nr/2; ++i) {
            char t = buf[i];
            buf[i] = buf[nr-1-i];
            buf[nr-1-i] = t;
        }
        if (write(outfd, buf, nr) != nr) { perror("write"); break; }
        processed += nr;
        remaining -= chunk;
        char pct[16];
        int p = (int)((processed * 100) / block);
        int len = snprintf(pct, sizeof(pct), "\r%3d%%", p);
        write(STDOUT_FILENO, pct, len);
    }

    write(STDOUT_FILENO, "\n", 1);
    close(infd);
    close(outfd);
    return EXIT_SUCCESS;
}
