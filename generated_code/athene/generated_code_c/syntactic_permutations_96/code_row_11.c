#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 40

char* generate_salt(int length) {
    char *salt = malloc(length + 1);
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; ++i) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[length] = '\0';
    return salt;
}

char* hash_password(const char *password, const char *salt) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, salt, strlen(salt));
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    char *hashed = malloc(HASH_LENGTH + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
    hashed[HASH_LENGTH] = '\0';
    return hashed;
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s and salted hash: %s in the database\n", username, salted_hash);
}

int main() {
    srand(time(NULL));

    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt(SALT_LENGTH);
    char *hashed_password = hash_password(password, salt);
    char *salted_hash = malloc(strlen(salt) + strlen(hashed_password) + 1);
    strcpy(salted_hash, salt);
    strcat(salted_hash, hashed_password);

    store_in_database(username, salted_hash);

    free(salt);
    free(hashed_password);
    free(salted_hash);

    return 0;
}