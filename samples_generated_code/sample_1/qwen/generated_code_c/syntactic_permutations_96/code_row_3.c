#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT "somesalt"

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[MAX_PASSWORD_LENGTH + strlen(SALT) + 1];

    strcpy(salted_password, salt);
    strcat(salted_password, password);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(digest, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_output[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, SALT, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    // Here you would typically store the username and hashed_password in a database
    // For demonstration purposes, we're just printing them

    return 0;
}