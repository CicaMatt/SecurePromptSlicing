#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        salt[i] = 'a' + (rand() % 26);
    }
    salt[len] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char digest[HASH_LEN];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < HASH_LEN; ++i) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hash[(HASH_LEN * 2) + SALT_LEN + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, hash);

    strcat(hash, salt);

    printf("Stored in database: %s\n", hash);

    return 0;
}