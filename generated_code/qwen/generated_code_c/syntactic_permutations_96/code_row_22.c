#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, int length) {
    if (!RAND_bytes(salt, length)) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    unsigned char salted_password[PASSWORD_LENGTH + SALT_LENGTH];

    // Concatenate salt and password
    memcpy(salted_password, salt, SALT_LENGTH);
    memcpy(salted_password + SALT_LENGTH, password, PASSWORD_LENGTH);

    // Hash the concatenated string
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salted_password, PASSWORD_LENGTH + SALT_LENGTH);
    SHA256_Final(hash, &sha_ctx);
}

void store_in_database(const unsigned char *username, const unsigned char *salt, const unsigned char *hash) {
    // Simulate storing in a database
    printf("Storing user:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHash: ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    unsigned char username[USERNAME_LENGTH];
    unsigned char password[PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hash);

    store_in_database(username, salt, hash);

    return 0;
}