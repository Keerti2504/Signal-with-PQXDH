#ifndef DOUBLE_RATCHET_H
#define DOUBLE_RATCHET_H

#include <stdint.h>
#include <stddef.h>  // Include for size_t

typedef struct {
    void *session;  // Opaque session pointer
} double_ratchet_state;

void initialize_ratchet(double_ratchet_state *state);
void encrypt_ratchet_message(double_ratchet_state *state, const uint8_t *plaintext, size_t plaintext_len, uint8_t *ciphertext, size_t *ciphertext_len);
void decrypt_ratchet_message(double_ratchet_state *state, const uint8_t *ciphertext, size_t ciphertext_len, uint8_t *plaintext, size_t *plaintext_len);

#endif // DOUBLE_RATCHET_H

