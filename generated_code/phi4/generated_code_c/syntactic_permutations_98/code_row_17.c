#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100

void hash_password(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from username input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from password input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }

        hash_password(password, hash);

        printf("Username: %s\n", username);
        printf("Hashed Password: ");
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");

        // Here you would normally insert the username and hashed password into a database
    }

    return 0;
}
