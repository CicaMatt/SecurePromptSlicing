#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 128
#define SALT_LEN 16

void generateSalt(char *salt, int len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, len, fp);
    fclose(fp);
}

void hashPassword(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN];
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + SALT_LEN + 1];

    printf("Enter username: ");
    if (fgets(username, USERNAME_LEN, stdin) == NULL) {
        perror("Failed to read username");
        exit(EXIT_FAILURE);
    }
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LEN, stdin) == NULL) {
        perror("Failed to read password");
        exit(EXIT_FAILURE);
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    generateSalt(salt, SALT_LEN);

    hashPassword(password, salt, hashed_password);
    memcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt, SALT_LEN);
    hashed_password[(SHA256_DIGEST_LENGTH * 2) + SALT_LEN] = '\0';

    FILE *fp = fopen("registration.txt", "a");
    if (fp == NULL) {
        perror("Failed to open registration file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "Username: %s, Hashed Password with Salt: %s\n", username, hashed_password);
    fclose(fp);

    printf("Registration successful!\n");

    return 0;
}