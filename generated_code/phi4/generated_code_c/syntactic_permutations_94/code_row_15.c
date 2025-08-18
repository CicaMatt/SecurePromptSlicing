#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SALT_SIZE 16

void generate_salt(uint8_t *salt) {
    for (int i = 0; i < SALT_SIZE; ++i) {
        salt[i] = rand() % 256;
    }
}

uint32_t hash_function(uint8_t *data, size_t len) {
    uint32_t hash = 5381;
    while (len--) {
        hash = ((hash << 5) + hash) + (*data++);
    }
    return hash;
}

void hash_password(const char *password, const uint8_t *salt, uint8_t hashed_password[4]) {
    size_t len = strlen(password);
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        password[len++] = salt[i];
    }
    uint32_t hash = hash_function((uint8_t *)password, len);
    memcpy(hashed_password, &hash, sizeof(hash));
}

int main() {
    char username[50], password[100];
    uint8_t salt[SALT_SIZE];
    uint8_t hashed_password[4];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password (in hex): ");
    for (int i = 0; i < sizeof(hashed_password); ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}