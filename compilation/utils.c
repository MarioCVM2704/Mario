#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "utils.h"

char* hacherMotDePasse(const char *mdp, char *hashStr) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)mdp, strlen(mdp), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashStr + (i * 2), "%02x", hash[i]);
    }
    hashStr[64] = '\0';
    return hashStr;
}