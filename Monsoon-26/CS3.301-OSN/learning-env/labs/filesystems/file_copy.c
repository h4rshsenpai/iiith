#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    int input = open(argv[1], O_RDONLY);
    if (input < 0) {
        perror("open source");
        return 1;
    }

    int output = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output < 0) {
        perror("open destination");
        close(input);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(input, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(output, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(input);
            close(output);
            return 1;
        }
    }

    if (bytes_read < 0) {
        perror("read");
    }

    close(input);
    close(output);
    return bytes_read < 0 ? 1 : 0;
}
