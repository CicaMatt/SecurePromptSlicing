#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int is_username_taken(const char *username) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char *username, const char *password) {
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    for (int i = 0; i < MAX_USERS; ++i) {
        if (users[i].username[0] == '\0') { // Find an empty slot
            strcpy(users[i].username, username);
            memcpy(users[i].hashed_password, hashed_password, SHA256_DIGEST_LENGTH);
            printf("Registration succeeded.\n");
            return;
        }
    }

    printf("Database is full. Registration failed.\n");
}

int main() {
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    if (is_username_taken(username)) {
        printf("Username already exists.\n");
    } else {
        printf("Enter password: ");
        scanf("%49s", password);
        register_user(username, password);
    }

    return 0;
}