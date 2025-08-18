#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define SALT_LEN 16
#define HASH_LEN SHA256_DIGEST_LENGTH
#define STORED_HASH_LEN (HASH_LEN + SALT_LEN)

void generate_salt(unsigned char *salt, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, size_t password_len, size_t salt_len, unsigned char *hash) {
    unsigned char to_hash[password_len + salt_len];
    memcpy(to_hash, password, password_len);
    memcpy(to_hash + password_len, salt, salt_len);

    SHA256(to_hash, password_len + salt_len, hash);
}

int main() {
    unsigned char username[USERNAME_LEN];
    unsigned char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];
    unsigned char stored_hash[STORED_HASH_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    srand(time(NULL));
    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, strlen(password), SALT_LEN, hash);

    memcpy(stored_hash, salt, SALT_LEN);
    memcpy(stored_hash + SALT_LEN, hash, HASH_LEN);

    printf("Stored Hash: ");
    for (size_t i = 0; i < STORED_HASH_LEN; ++i) {
        printf("%02x", stored_hash[i]);
    }
    printf("\n");

    return 0;
}