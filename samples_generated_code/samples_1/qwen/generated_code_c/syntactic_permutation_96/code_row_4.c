#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define SALT_LENGTH 8
#define HASHED_PASSWORD_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, int length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Failed to generate random bytes\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hashed_output) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA256_Update(&sha_ctx, password, strlen((char*)password));
    SHA256_Final(hashed_output, &sha_ctx);
}

int main() {
    unsigned char username[USERNAME_LENGTH];
    unsigned char password[PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    // Simulating storing in a database
    printf("\nStored Data:\n");
    printf("Username: %s\n", username);
    printf("Salt:     ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASHED_PASSWORD_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}