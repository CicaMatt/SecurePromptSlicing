#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)

void generate_salt(char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[256];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);

    SHA256((unsigned char *)salted_password, strlen(salted_password), (unsigned char *)&digest);
    for (int i = 0; i < SALT_LENGTH; ++i) {
        hashed_password[i] = salt[i];
    }
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[SALT_LENGTH + i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Simulate storing in a database
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    return 0;
}