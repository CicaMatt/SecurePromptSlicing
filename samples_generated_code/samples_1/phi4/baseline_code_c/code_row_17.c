#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void hashPassword(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int main() {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    // Simulate insertion into a database
    FILE *file = fopen("users.db", "a");
    if (file != NULL) {
        fprintf(file, "%s:%s\n", username, hashedPassword);
        fclose(file);
    } else {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    printf("User added successfully.\n");

    return 0;
}