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

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int username_exists(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (username_exists(username)) {
        printf("Registration failed: Username already exists.\n");
        return;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    strcpy(users[user_count].username, username);
    memcpy(users[user_count].hashed_password, hashed_password, SHA256_DIGEST_LENGTH);
    
    user_count++;
    printf("Registration succeeded: Welcome %s!\n", first_name);
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}
