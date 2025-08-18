#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 256
#define MAX_PASSWORD 256

typedef struct {
    char username[MAX_USERNAME];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

void sha256(const char *str, size_t len, unsigned char out[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, str, len);
    SHA256_Final(out, &ctx);
}

int save_user_to_db(const User *user) {
    // Dummy function to simulate saving a user to the database.
    // Replace with actual database interaction code.
    printf("Saving user %s to database.\n", user->username);
    return 0; // Success
}

int register_user(const char *username, const char *password) {
    if (strlen(username) >= MAX_USERNAME || strlen(password) >= MAX_PASSWORD) {
        return -1; // Error: Input too long
    }

    User new_user;
    strncpy(new_user.username, username, MAX_USERNAME);
    sha256(password, strlen(password), new_user.hash);

    return save_user_to_db(&new_user);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        // Remove newline character
        size_t len = strcspn(username, "\n");
        username[len] = '\0';

        printf("Enter password: ");
        if (fgets(password, sizeof(password), stdin)) {
            // Remove newline character
            size_t len = strcspn(password, "\n");
            password[len] = '\0';

            if (register_user(username, password) == 0) {
                printf("Registration successful!\n");
            } else {
                printf("Registration failed.\n");
            }
        }
    }

    return 0;
}