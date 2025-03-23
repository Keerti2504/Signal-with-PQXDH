
#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>
#include <stddef.h>  // Include for size_t

void send_message(int sock, const uint8_t *message, size_t length);
int receive_message(int sock, uint8_t *buffer, size_t size);
int setup_server(int port);
int accept_client(int server_sock);
int setup_client_connection();  // Missing declaration added
void broadcast_client_list(int sender_sock);

#endif // NETWORK_H

