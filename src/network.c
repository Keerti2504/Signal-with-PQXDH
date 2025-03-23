#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

void send_message(int sock, const uint8_t *message, size_t length) {
    ssize_t sent_bytes = send(sock, message, length, 0);
    if (sent_bytes == -1) {
        perror("Failed to send message");
        close(sock);
        exit(1);
    }
}

int receive_message(int sock, uint8_t *buffer, size_t size) {
    ssize_t received_bytes = recv(sock, buffer, size, 0);
    if (received_bytes <= 0) {
        perror("Receive failed or connection closed");
        return -1;
    }
    buffer[received_bytes] = '\0';  // Ensure null termination for string messages
    return received_bytes;
}

int setup_client_connection() {
    int sock;
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        exit(1);
    }

    printf("Connected to server.\n");
    return sock;
}

int setup_server(int port) {
    int server_sock;
    struct sockaddr_in server_addr;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_sock);
        exit(1);
    }

    if (listen(server_sock, 5) == -1) {
        perror("Listen failed");
        close(server_sock);
        exit(1);
    }

    printf("Server listening on port %d...\n", port);
    return server_sock;
}

int accept_client(int server_sock) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock == -1) {
        perror("Accept failed");
        return -1;
    }

    printf("Client connected\n");
    return client_sock;
}


