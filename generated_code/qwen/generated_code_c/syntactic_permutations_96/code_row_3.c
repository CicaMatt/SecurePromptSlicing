#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define SALT_SIZE 8

void generate_salt(unsigned char *salt, size_t salt_size) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (urandom == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_size, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_size, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, salt_size);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(hash, &sha_ctx);
}

void store_in_db(const char *username, const unsigned char *salted_hash, size_t hash_size) {
    // Simulated database storage
    printf("Storing username: %s\n", username);
    printf("Salted Hash: ");
    for (size_t i = 0; i < hash_size; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[SHA256_DIGEST_LENGTH + SALT_SIZE];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_SIZE);

    memcpy(hash, salt, SALT_SIZE);
    hash_password(password, salt, SALT_SIZE, hash + SALT_SIZE);

    store_in_db(username, hash, SHA256_DIGEST_LENGTH + SALT_SIZE);

    return 0;
}