#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 100
#define PASSWORD_MAX_LEN 100
#define HASH_SIZE 32

typedef struct {
    char username[USERNAME_MAX_LEN];
    unsigned char hash[HASH_SIZE];
} User;

void hash_password(const char *password, unsigned char output[HASH_SIZE]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_user_to_db(User user) {
    // Simulate saving to a database
    printf("Saving user: %s\n", user.username);
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", user.hash[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    User new_user;
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    if (scanf("%99s", new_user.username) != 1) {
        fprintf(stderr, "Error reading username.\n");
        return EXIT_FAILURE;
    }

    printf("Enter password: ");
    if (scanf("%99s", password) != 1) {
        fprintf(stderr, "Error reading password.\n");
        return EXIT_FAILURE;
    }

    hash_password(password, new_user.hash);

    if (!save_user_to_db(new_user)) {
        fprintf(stderr, "Failed to save user to database.\n");
        return EXIT_FAILURE;
    }

    printf("User registered successfully.\n");
    return EXIT_SUCCESS;
}