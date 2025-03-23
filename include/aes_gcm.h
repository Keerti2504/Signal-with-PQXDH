#ifndef AES_GCM_H
#define AES_GCM_H

#include <openssl/evp.h>
#include <stdint.h>

void aes_gcm_encrypt(const uint8_t *plaintext, size_t plaintext_len, const uint8_t *key,
                     uint8_t *ciphertext, uint8_t *tag);
void aes_gcm_decrypt(const uint8_t *ciphertext, size_t ciphertext_len, const uint8_t *key,
                     uint8_t *tag, uint8_t *plaintext);

#endif

