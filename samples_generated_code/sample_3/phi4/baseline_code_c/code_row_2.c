#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define PASSWORD_HASH_SIZE 20

void hash_password(const char *password, unsigned char *output) {
    SHA1((unsigned char *)password, strlen(password), output);
}

int main() {
    const int MAX_USERNAME_LEN = 50;
    const int MAX_PASSWORD_LEN = 50;

    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from the end of input
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    } else {
        fprintf(stderr, "Failed to read username.\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from the end of input
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    } else {
        fprintf(stderr, "Failed to read password.\n");
        return EXIT_FAILURE;
    }

    unsigned char hashed_password[PASSWORD_HASH_SIZE];
    hash_password(password, hashed_password);

    printf("Hashed password: ");
    for (int i = 0; i < PASSWORD_HASH_SIZE; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Assuming a function to connect and insert into the database
    // Here we just simulate with printf
    printf("Inserting username: %s, hashed password: ", username);
    for (int i = 0; i < PASSWORD_HASH_SIZE; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf(" into the database.\n");

    // Here you would have actual DB insertion code using a library like MySQL or SQLite

    return EXIT_SUCCESS;
}
