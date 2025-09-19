#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define SALT_LEN 16
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, size_t len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, len, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_len, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, salt_len);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, SALT_LEN, hash);

    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LEN; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASH_LEN; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Code to insert username, salt, and hashed password into the database goes here

    return 0;
}