#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h> // For SHA256 hashing

#define SALT_LENGTH 16
#define HASH_LENGTH 64
#define BUFFER_SIZE 100

char* generate_salt(int length) {
    char *salt = malloc(length + 1);
    if (salt == NULL) return NULL;
    for (int i = 0; i < length; i++) {
        salt[i] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[rand() % 62];
    }
    salt[length] = '\0';
    return salt;
}

char* hash_password(const char *password, const char *salt) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Update(&ctx, salt, strlen(salt));
    SHA256_Final(digest, &ctx);

    char *hash = malloc(HASH_LENGTH + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
    hash[HASH_LENGTH] = '\0';
    return hash;
}

void store_user(const char *username, const char *hashed_password) {
    // Simulate storing in a database
    printf("Storing user: %s with hashed password: %s\n", username, hashed_password);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt(SALT_LENGTH);
    if (salt == NULL) {
        fprintf(stderr, "Failed to generate salt.\n");
        return 1;
    }

    char *hashed_password = hash_password(password, salt);
    if (hashed_password == NULL) {
        free(salt);
        fprintf(stderr, "Failed to hash password.\n");
        return 1;
    }

    // Append the salt to the hashed password
    char *stored_hash = malloc(strlen(hashed_password) + strlen(salt) + 1);
    strcpy(stored_hash, hashed_password);
    strcat(stored_hash, salt);

    store_user(username, stored_hash);

    free(salt);
    free(hashed_password);
    free(stored_hash);

    return 0;
}