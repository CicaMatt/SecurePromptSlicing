#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

char* generate_salt(int length) {
    char *salt = malloc(length + 1);
    if (salt == NULL) return NULL;
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        fclose(fp);
        free(salt);
        return NULL;
    }
    fread(salt, length, 1, fp);
    fclose(fp);
    salt[length] = '\0';
    for (int i = 0; i < length; ++i) {
        salt[i] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[salt[i] % 62];
    }
    return salt;
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    char input[1024];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), output);
}

int main() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt(SALT_LENGTH);
    if (salt == NULL) {
        fprintf(stderr, "Failed to generate salt.\n");
        return 1;
    }

    unsigned char hashed_password[HASH_LENGTH];
    hash_password(password, salt, hashed_password);

    // Concatenate salt and hashed password for storage
    char stored_hash[256];
    snprintf(stored_hash, sizeof(stored_hash), "%s%.*s", salt, HASH_LENGTH * 2, (char *)hashed_password);

    printf("Stored in database: %s\n", stored_hash);
    free(salt);
    return 0;
}