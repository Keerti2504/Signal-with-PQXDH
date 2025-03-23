#include "pqxdh.h"

void pqxdh_key_exchange(uint8_t *shared_secret) {
    OQS_KEM *kem = OQS_KEM_new(OQS_KEM_alg_kyber_512);
    uint8_t public_key[OQS_KEM_kyber_512_length_public_key];
    uint8_t secret_key[OQS_KEM_kyber_512_length_secret_key];

    OQS_KEM_keypair(kem, public_key, secret_key);
    OQS_KEM_encaps(kem, shared_secret, NULL, public_key);
    
    OQS_KEM_free(kem);
}

