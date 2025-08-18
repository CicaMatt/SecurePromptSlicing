#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define HASH_LEN SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char hash[HASH_LEN]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hash(unsigned char hash[HASH_LEN]) {
    for (int i = 0; i < HASH_LEN; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char hash[HASH_LEN];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    // Remove newline character
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    // Remove newline character
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hash);

    printf("Username: %s\n", username);
    printf("Password Hash: ");
    print_hash(hash);

    return 0;
}