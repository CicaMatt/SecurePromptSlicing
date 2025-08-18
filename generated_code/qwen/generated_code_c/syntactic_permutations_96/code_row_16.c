#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 8
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, size_t salt_length) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_length, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_length, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);

    SHA256_Update(&sha_ctx, salt, salt_length);
    SHA256_Update(&sha_ctx, password, strlen(password));

    SHA256_Final(hash, &sha_ctx);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, SALT_LENGTH, hash);

    printf("Salt (hex): ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password (hex): ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Here you would typically store the concatenation of salt and hash in your database
    // For demonstration, we're not connecting to a database

    return 0;
}