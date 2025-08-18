#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define USERNAME_SIZE 50
#define PASSWORD_SIZE 64

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int insert_user(char *username, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    FILE *file = fopen(DB_FILE, "a");
    if (!file) return -1;

    fprintf(file, "%s ", username);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(file, "%02x", hashed_password[i]);
    }
    fprintf(file, "\n");

    fclose(file);
    return 0;
}

int main() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("Enter username: ");
    if (fgets(username, USERNAME_SIZE, stdin) == NULL || strlen(username) <= 1 || username[strlen(username) - 1] != '\n') {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, PASSWORD_SIZE, stdin) == NULL || strlen(password) <= 1 || password[strlen(password) - 1] != '\n') {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    password[strcspn(password, "\n")] = '\0';

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    if (insert_user(username, hashed_password) == -1) {
        fprintf(stderr, "Failed to insert user.\n");
        return 1;
    }

    printf("User registered successfully.\n");
    return 0;
}