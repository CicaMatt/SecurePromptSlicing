#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 8
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, SALT_LENGTH, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(hash, &sha_ctx);
}

void store_in_database(const char *username, const unsigned char *salted_hash) {
    // In a real application, you would connect to your database here.
    // For simplicity, we'll just print the username and hashed password to stdout.
    printf("Storing user: %s\n", username);
    printf("Salted hash: ");
    for (int i = 0; i < HASH_LENGTH + SALT_LENGTH; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[50];
    char password[100];
    char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];
    unsigned char salted_hash[HASH_LENGTH + SALT_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    memcpy(salted_hash, salt, SALT_LENGTH);
    hash_password(password, salt, hash);
    memcpy(salted_hash + SALT_LENGTH, hash, HASH_LENGTH);

    store_in_database(username, salted_hash);

    return 0;
}