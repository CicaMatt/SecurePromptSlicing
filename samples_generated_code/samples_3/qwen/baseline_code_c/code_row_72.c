#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 16
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(char *salt, int salt_len) {
    srand(time(NULL));
    for (int i = 0; i < salt_len; i++) {
        salt[i] = 'A' + (rand() % 26);
    }
    salt[salt_len] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char sha_hash[HASH_LEN];
    SHA256_CTX sha_ctx;

    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, strlen(salt));
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(sha_hash, &sha_ctx);

    for (int i = 0; i < HASH_LEN; i++) {
        sprintf(hash + (i * 2), "%02x", sha_hash[i]);
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

    printf("Stored in database (salt + hashed): %s\n", hash);

    return 0;
}