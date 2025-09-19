#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 128

void hashPassword(const char *password, char *outputBuffer) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char hashedPassword[(SHA256_DIGEST_LENGTH * 2) + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    hashPassword(password, hashedPassword);

    printf("\nRegistration details:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashedPassword);

    return 0;
}