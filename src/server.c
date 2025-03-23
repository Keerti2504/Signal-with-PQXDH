#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "network.h"
#include "pqxdh.h"
#include "double_ratchet.h"
#include "aes_gcm.h"

#define MAX_CLIENTS 10

typedef struct {
    int id;
    int sock;
} client_t;

client_t clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_lock = PTHREAD_MUTEX_INITIALIZER;

void broadcast_client_list(int sender_sock) {
    char list_message[256] = "Connected Clients: ";
    pthread_mutex_lock(&clients_lock);
    for (int i = 0; i < client_count; i++) {
        char temp[10];
        sprintf(temp, "[%d] ", clients[i].id);
        strcat(list_message, temp);
    }
    pthread_mutex_unlock(&clients_lock);
    send_message(sender_sock, (uint8_t *)list_message, strlen(list_message));
}

void *handle_client(void *arg) {
    int client_sock = *(int *)arg;
    free(arg);
    
    int client_id = client_count + 1;  // Assign ID
    pthread_mutex_lock(&clients_lock);
    clients[client_count].id = client_id;
    clients[client_count].sock = client_sock;
    client_count++;
    pthread_mutex_unlock(&clients_lock);

    printf("Client %d connected.\n", client_id);

    uint8_t buffer[1024];
    while (1) {
        ssize_t received_len = receive_message(client_sock, buffer, sizeof(buffer));
        if (received_len <= 0) {
            printf("Client %d disconnected.\n", client_id);
            break;
        }

        char received_text[1024];
        memcpy(received_text, buffer, received_len);
        received_text[received_len] = '\0';

        int recipient_id;
        char message_text[1024];
        if (sscanf(received_text, "%d: %[^\n]", &recipient_id, message_text) != 2) {
            continue; // Ignore invalid messages
        }

        pthread_mutex_lock(&clients_lock);
        int found = 0;
        for (int i = 0; i < client_count; i++) {
            if (clients[i].id == recipient_id) {
                send_message(clients[i].sock, (uint8_t *)message_text, strlen(message_text));
                found = 1;
                break;
            }
        }
        pthread_mutex_unlock(&clients_lock);

        if (!found) {
            char error_msg[] = "Recipient not found.\n";
            send_message(client_sock, (uint8_t *)error_msg, strlen(error_msg));
        }
    }

    close(client_sock);
    return NULL;
}

int main() {
    int server_sock = setup_server(12345);

    while (1) {
        int *client_sock = malloc(sizeof(int));
        *client_sock = accept_client(server_sock);
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, client_sock);
        pthread_detach(thread);
    }
    return 0;
}

