#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t length) {
    srand(time(NULL));
    for (size_t i = 0; i < length; ++i) {
        salt[i] = 'A' + rand() % 91;
    }
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    unsigned char salted_password[MAX_PASSWORD_LENGTH + SALT_LENGTH];
    
    memcpy(salted_password, password, strlen(password));
    memcpy(salted_password + strlen(password), salt, SALT_LENGTH);
    
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salted_password, strlen(password) + SALT_LENGTH);
    SHA256_Final(hash, &sha_ctx);
}

void store_in_db(const char *username, const unsigned char *hash, const char *salt) {
    // Simulated database storage
    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\nSalt: %s\n", salt);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1] = {0};
    unsigned char hash[HASH_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hash);

    store_in_db(username, hash, salt);

    return 0;
}