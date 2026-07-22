#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    const char *message = argc > 1 ? argv[1] : "hello";

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_port = htons(PORT);

    sendto(sock, message, strlen(message), 0, (struct sockaddr *)&server, sizeof(server));

    char buffer[BUFFER_SIZE];
    socklen_t server_len = sizeof(server);
    ssize_t received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr *)&server, &server_len);
    if (received < 0) {
        perror("recvfrom");
        close(sock);
        return 1;
    }

    buffer[received] = '\0';
    printf("reply: %s\n", buffer);

    close(sock);
    return 0;
}
