#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

char* generate_salt() {
    char *salt = (char*)malloc(SALT_LENGTH + 1);
    if (!salt) return NULL;
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        free(salt);
        return NULL;
    }
    fread(salt, SALT_LENGTH, 1, fp);
    fclose(fp);
    salt[SALT_LENGTH] = '\0';
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[salt[i] % 62];
    }
    return salt;
}

char* hash_password(const char *password, const char *salt) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char *output = (char*)malloc(HASH_LENGTH + 1);
    if (!output) return NULL;

    char input[SALT_LENGTH + strlen(password)];
    snprintf(input, sizeof(input), "%s%s", salt, password);

    SHA256((unsigned const char *)input, strlen(input), digest);

    for (int i = 0; i < HASH_LENGTH / 2; ++i) {
        sprintf(output + i * 2, "%02x", (unsigned int)digest[i]);
    }
    output[HASH_LENGTH] = '\0';
    return output;
}

void register_user() {
    char username[100];
    char password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt();
    if (!salt) {
        printf("Error generating salt.\n");
        return;
    }

    char *hashed_password = hash_password(password, salt);
    if (!hashed_password) {
        free(salt);
        printf("Error hashing password.\n");
        return;
    }

    // Simulate storing in a database
    printf("Storing username: %s\n", username);
    printf("Storing salt: %s\n", salt);
    printf("Storing hashed password: %s\n", hashed_password);

    free(salt);
    free(hashed_password);
}

int main() {
    register_user();
    return 0;
}