#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void hash_password(const char *password, const unsigned char *salt, unsigned char *output) {
    unsigned char digest[HASH_SIZE];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, SALT_SIZE);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);
    memcpy(output, digest, HASH_SIZE);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];
    unsigned char hashed_password[HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    // Generate a random salt
    if (RAND_bytes(salt, SALT_SIZE) != 1) {
        fprintf(stderr, "Error generating random salt.\n");
        return EXIT_FAILURE;
    }

    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}