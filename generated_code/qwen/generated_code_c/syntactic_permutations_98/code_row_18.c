#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin)) {
        // Remove newline character from the input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin)) {
        // Remove newline character from the input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    hash_password(password, hashed_password);

    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }

    fprintf(file, "Username: %s\nHashed Password: %s\n", username, hashed_password);
    fclose(file);

    printf("Registration successful!\n");

    return EXIT_SUCCESS;
}


Make sure to link the OpenSSL library when compiling this code using `-lssl -lcrypto` flags. For example:

gcc -o registration_page registration_page.c -lssl -lcrypto