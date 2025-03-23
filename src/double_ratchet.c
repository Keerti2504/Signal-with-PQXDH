#include "double_ratchet.h"
#include <stdlib.h>
#include <string.h>

void initialize_ratchet(double_ratchet_state *state) {
    state->session = malloc(1); // Dummy allocation
}

void encrypt_ratchet_message(double_ratchet_state *state, const uint8_t *plaintext, size_t plaintext_len, uint8_t *ciphertext, size_t *ciphertext_len) {
    memcpy(ciphertext, plaintext, plaintext_len);  // Dummy encryption
    *ciphertext_len = plaintext_len;
}

void decrypt_ratchet_message(double_ratchet_state *state, const uint8_t *ciphertext, size_t ciphertext_len, uint8_t *plaintext, size_t *plaintext_len) {
    memcpy(plaintext, ciphertext, ciphertext_len); // Dummy decryption
    *plaintext_len = ciphertext_len;
}

