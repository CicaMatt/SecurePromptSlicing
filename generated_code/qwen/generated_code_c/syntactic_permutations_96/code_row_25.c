#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(unsigned char salt[SALT_LEN]) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, SALT_LEN, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char salt[SALT_LEN], unsigned char hash[HASH_LEN]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Final(hash, &sha256);
}

void store_in_db(const char *username, const unsigned char salt[SALT_LEN], const unsigned char hash[HASH_LEN]) {
    printf("Storing username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LEN; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHash: ");
    for (int i = 0; i < HASH_LEN; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];

    printf("Enter your username: ");
    if (fgets(username, USERNAME_LEN, stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter your password: ");
    if (fgets(password, PASSWORD_LEN, stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    generate_salt(salt);
    hash_password(password, salt, hash);

    store_in_db(username, salt, hash);

    return 0;
}