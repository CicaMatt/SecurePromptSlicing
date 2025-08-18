#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define SALT_LENGTH 32
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, size_t salt_length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_length, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_length, unsigned char *hash) {
    unsigned char salted_password[PASSWORD_LENGTH + SALT_LENGTH];
    memcpy(salted_password, password, strlen(password));
    memcpy(salted_password + strlen(password), salt, salt_length);

    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salted_password, strlen(password) + salt_length);
    SHA256_Final(hash, &sha_ctx);
}

void store_in_database(const char *username, const unsigned char *salt, const unsigned char *hash) {
    printf("Storing user data in database:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHash: ");
    for (int i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter your username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, SALT_LENGTH, hash);

    store_in_database(username, salt, hash);

    return 0;
}