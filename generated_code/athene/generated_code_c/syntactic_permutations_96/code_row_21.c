#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char digest[HASH_SIZE];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, SALT_SIZE);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    memcpy(output, digest, HASH_SIZE);
}

void store_in_database(const char *username, const unsigned char *salt_hashed_password) {
    // Placeholder for database storage logic
    printf("Storing username: %s\n", username);
    printf("Storing salt+hash: ");
    for (int i = 0; i < SALT_SIZE + HASH_SIZE; i++) {
        printf("%02x", salt_hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];
    unsigned char salt_hashed_password[SALT_SIZE + HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);
    memcpy(salt_hashed_password, salt, SALT_SIZE);
    memcpy(salt_hashed_password + SALT_SIZE, hash, HASH_SIZE);

    store_in_database(username, salt_hashed_password);

    return 0;
}