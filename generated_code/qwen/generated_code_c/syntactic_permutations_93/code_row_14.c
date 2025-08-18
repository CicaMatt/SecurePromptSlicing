#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

void insert_credentials(const char *username, const char *hashed_password) {
    FILE *file = fopen("credentials.txt", "a");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Username: %s\nPassword: %s\n\n", username, hashed_password);
    fclose(file);
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + 1];

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        username[strcspn(username, "\n")] = '\0'; // Remove newline character
    }

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        password[strcspn(password, "\n")] = '\0'; // Remove newline character
    }

    hash_password(password, hashed_password);
    insert_credentials(username, hashed_password);

    printf("Credentials stored successfully.\n");

    return 0;
}