#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LEN 16
#define HASH_LEN 64
#define MAX_USERNAME_LEN 256
#define MAX_PASSWORD_LEN 256

void generate_salt(char *salt, size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        salt[i] = 'a' + rand() % ('z' - 'a');
    }
    salt[len - 1] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    char input[MAX_PASSWORD_LEN + SALT_LEN];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)input, strlen(input), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", hash[i]);
    }
    hashed[HASH_LEN] = '\0';
}

void store_credentials(const char *username, const char *hashed_password_with_salt) {
    FILE *fp = fopen("database.txt", "a");
    if (fp == NULL) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s:%s\n", username, hashed_password_with_salt);
    fclose(fp);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hashed_password[HASH_LEN + SALT_LEN + 1];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hashed_password);
    snprintf(hashed_password, sizeof(hashed_password), "%s$%s", salt, hashed_password);

    store_credentials(username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}