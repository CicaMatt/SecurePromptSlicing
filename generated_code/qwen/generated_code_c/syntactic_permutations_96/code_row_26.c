#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t salt_len) {
    srand(time(NULL));
    for (size_t i = 0; i < salt_len; ++i) {
        salt[i] = 'A' + (rand() % ('Z' - 'A'));
    }
    salt[salt_len] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char sha256_hash[HASH_LEN];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Final(sha256_hash, &sha256);

    for (int i = 0; i < HASH_LEN; i++) {
        sprintf(hash + (i * 2), "%02x", sha256_hash[i]);
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hash[HASH_LEN * 2 + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hash);

    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hash);

    // Here you would typically store the username, salt, and hash in your database
    // For demonstration purposes, we're just printing them out.

    return 0;
}