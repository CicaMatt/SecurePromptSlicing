#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < salt_length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA512_CTX sha_ctx;
    SHA512_Init(&sha_ctx);
    SHA512_Update(&sha_ctx, password, strlen(password));
    SHA512_Update(&sha_ctx, salt, SALT_LENGTH);
    SHA512_Final(hash, &sha_ctx);
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    unsigned char hash[SHA512_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, hash);

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Simulate database insertion
    printf("Inserting into database...\n");
    printf("Username: %s, Salt: %s, Hashed Password: ", username, salt);
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}