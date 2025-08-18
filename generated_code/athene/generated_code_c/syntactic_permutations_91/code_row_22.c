#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

typedef struct {
    char *username;
    char *password_hash;
} User;

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_user_to_db(User *user) {
    // Simulate database insertion
    printf("Inserting user into the database:\n");
    printf("Username: %s\n", user->username);
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", user->password_hash[i]);
    }
    printf("\n");
    return 1; // Simulate success
}

int register_user(const char *username, const char *password) {
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    User new_user = {
        .username = strdup(username),
        .password_hash = (char *)malloc(SHA256_DIGEST_LENGTH)
    };
    memcpy(new_user.password_hash, password_hash, SHA256_DIGEST_LENGTH);

    if (!save_user_to_db(&new_user)) {
        free(new_user.username);
        free(new_user.password_hash);
        return 0;
    }

    free(new_user.username);
    free(new_user.password_hash);
    return 1;
}

int main() {
    const char *username = "exampleUser";
    const char *password = "securePassword123";

    if (register_user(username, password)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}