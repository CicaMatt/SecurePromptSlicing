#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hash_buffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_buffer[i*2], "%02x", hash[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Salted Hashed Password: %s\n", hashed_password);

    // Simulate database insertion
    printf("Inserting into database:\n");
    printf("Username: %s, Salt: %.*s, Hashed Password: %s\n", username, (int)SALT_LENGTH, salt, hashed_password);

    return 0;
}