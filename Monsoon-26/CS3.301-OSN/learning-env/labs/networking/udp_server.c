#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main(void) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(sock);
        return 1;
    }

    printf("UDP server listening on 127.0.0.1:%d\n", PORT);

    char buffer[BUFFER_SIZE];
    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);

    ssize_t received = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                                (struct sockaddr *)&client, &client_len);
    if (received < 0) {
        perror("recvfrom");
        close(sock);
        return 1;
    }

    buffer[received] = '\0';
    printf("received: %s\n", buffer);

    const char *reply = "server received your message";
    sendto(sock, reply, strlen(reply), 0, (struct sockaddr *)&client, client_len);

    close(sock);
    return 0;
}
