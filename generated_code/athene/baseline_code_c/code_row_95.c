#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)

void generate_salt(char *salt, int length) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, length, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char sha256[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, SALT_LENGTH);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(sha256, &ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hash + (i * 2), "%02x", sha256[i]);
    }
}

void store_to_database(const char *username, const char *hashed_password_and_salt) {
    printf("Storing to database:\nUsername: %s\nHashed Password and Salt: %s\n", username, hashed_password_and_salt);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt, SALT_LENGTH);
    salt[SALT_LENGTH] = '\0';

    char hash[HASH_LENGTH + 1];
    hash_password(password, salt, hash);

    char hashed_password_and_salt[HASH_LENGTH + SALT_LENGTH + 1];
    strcpy(hashed_password_and_salt, hash);
    strcat(hashed_password_and_salt, salt);

    store_to_database(username, hashed_password_and_salt);

    return 0;
}