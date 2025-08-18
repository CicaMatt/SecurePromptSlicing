#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

typedef struct {
    char *username;
    char *password_hash;
} User;

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int save_user_to_db(User user) {
    // Dummy function to simulate saving user to database
    printf("Saving user: %s with hashed password: ", user.username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", (unsigned int)user.password_hash[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    char username[100];
    char password[100];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, password_hash);

    User user = {
        .username = strdup(username),
        .password_hash = (char *)malloc(SHA256_DIGEST_LENGTH)
    };
    memcpy(user.password_hash, password_hash, SHA256_DIGEST_LENGTH);

    if (save_user_to_db(user)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    free(user.username);
    free(user.password_hash);

    return 0;
}