#include "network.h"
#include "double_ratchet.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 1024

int sock;
double_ratchet_state dr_state;

void *receive_messages(void *arg) {
    uint8_t buffer[MAX_MESSAGE_SIZE];
    size_t received_len;

    while (1) {
        received_len = receive_message(sock, buffer, sizeof(buffer));
        if (received_len > 0) {
            uint8_t decrypted[MAX_MESSAGE_SIZE];
            size_t decrypted_len;

            decrypt_ratchet_message(&dr_state, buffer, received_len, decrypted, &decrypted_len);
            decrypted[decrypted_len] = '\0';  // Null-terminate

            printf("\n[New Message from Client]: %s\n", decrypted);
            printf("Enter recipient ID: ");  // Reprint prompt
            fflush(stdout);
        }
    }
    return NULL;
}

int main() {
    sock = setup_client_connection();
    initialize_ratchet(&dr_state);

    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, NULL);
    pthread_detach(recv_thread); // Keep receiving in background

    while (1) {
        char message[MAX_MESSAGE_SIZE];
        uint8_t ciphertext[MAX_MESSAGE_SIZE];
        size_t ciphertext_len;
        int recipient_id;

        printf("Enter recipient ID: ");
        if (scanf("%d", &recipient_id) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        getchar(); // Consume newline

        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0;

        char formatted_message[MAX_MESSAGE_SIZE];
        snprintf(formatted_message, sizeof(formatted_message) - 1, "%d: %.900s", recipient_id, message);
formatted_message[sizeof(formatted_message) - 1] = '\0';  // Ensure null termination


        encrypt_ratchet_message(&dr_state, (uint8_t *)formatted_message, strlen(formatted_message), ciphertext, &ciphertext_len);
        send_message(sock, ciphertext, ciphertext_len);
    }

    close(sock);
    return 0;
}



 
