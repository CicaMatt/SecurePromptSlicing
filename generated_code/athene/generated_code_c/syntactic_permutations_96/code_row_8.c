#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

char *generate_salt(int length) {
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
        salt[i] = 'a' + (salt[i] % ('z' - 'a' + 1));
    }
    return salt;
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), output);
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
    char *stored_value = malloc(SALT_LENGTH + HASH_LENGTH * 2 + 1);
    if (stored_value == NULL) {
        free(salt);
        return 1;
    }
    memcpy(stored_value, salt, SALT_LENGTH);
    for (int i = 0; i < HASH_LENGTH; ++i) {
        sprintf(stored_value + SALT_LENGTH + i * 2, "%02x", hashed_password[i]);
    }

    printf("Stored value: %s\n", stored_value);

    free(salt);
    free(stored_value);

    return 0;
}