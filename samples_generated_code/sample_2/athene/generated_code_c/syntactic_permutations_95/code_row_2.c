#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 40

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA1((unsigned char *)input, strlen(input), digest);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
    hashed[HASH_LENGTH] = '\0';
}

void store_user(const char *username, const char *hashed_password) {
    FILE *file = fopen("users.db", "a");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    fprintf(file, "%s:%s\n", username, hashed_password);
    fclose(file);
}

int main() {
    char username[256], password[256];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    strcat(hashed_password, salt);

    store_user(username, hashed_password);

    printf("User registered successfully.\n");

    return 0;
}