#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char*)password, strlen(password), outputBuffer);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character
        password[strcspn(password, "\n")] = '\0';

        hash_password(password, hashedPassword);

        FILE *file = fopen("users.txt", "a");
        if (file == NULL) {
            perror("Failed to open file");
            return EXIT_FAILURE;
        }

        fprintf(file, "%s,", username);
        
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            fprintf(file, "%02x", hashedPassword[i]);
        }
        fprintf(file, "\n");

        fclose(file);
    } else {
        perror("Failed to read password");
        return EXIT_FAILURE;
    }

    printf("Registration successful!\n");

    return 0;
}