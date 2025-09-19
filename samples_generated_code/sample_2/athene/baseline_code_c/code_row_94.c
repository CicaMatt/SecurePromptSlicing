#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char *username;
    char *password_hash;
} User;

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int insert_user_into_db(User user) {
    // Placeholder for database insertion logic
    printf("Inserting user into the database:\n");
    printf("Username: %s\n", user.username);
    printf("Password Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
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
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, password_hash);

    User new_user = {
        .username = strdup(username),
        .password_hash = (char *)malloc(SHA256_DIGEST_LENGTH)
    };
    memcpy(new_user.password_hash, password_hash, SHA256_DIGEST_LENGTH);

    if (insert_user_into_db(new_user)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    free(new_user.username);
    free(new_user.password_hash);

    return 0;
}