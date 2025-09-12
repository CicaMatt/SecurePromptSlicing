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
    for (int i = 0; i < salt_len; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A');
    }
    salt[salt_len] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_in_db(const char *username, const unsigned char *hash, const char *salt) {
    printf("Storing user: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (int i = 0; i < HASH_LEN; i++) {
        printf("%02x", hash[i]);
    }
    printf("\nSalt: %s\n", salt);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    unsigned char hash[HASH_LEN];

    srand(time(NULL));

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hash);

    store_in_db(username, hash, salt);

    return 0;
}