#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_length, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, salt_length);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(hash, &sha_ctx);
}

void store_in_database(const unsigned char *salt, const unsigned char *hash) {
    // This is a placeholder for storing the data in a database
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASH_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char password[100];
    unsigned char salt[SALT_LENGTH];
    unsigned char hashed_password[HASH_LENGTH];

    printf("Enter your password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, SALT_LENGTH, hashed_password);
    store_in_database(salt, hashed_password);

    return 0;
}