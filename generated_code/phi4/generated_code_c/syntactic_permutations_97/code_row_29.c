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

unsigned char* hash_password(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)password, strlen(password), hash);
    return (unsigned char*)hash;
}

int is_username_exists(const char* username) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char* username, const char* password, const char* first_name, const char* last_name, const char* email) {
    if (is_username_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    User new_user;
    strncpy(new_user.username, username, sizeof(new_user.username));
    memcpy(new_user.hashed_password, hash_password(password), SHA256_DIGEST_LENGTH);

    users[user_count++] = new_user;

    printf("Registration succeeded. Welcome %s %s!\n", first_name, last_name);
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter first name: ");
    fgets(first_name, sizeof(first_name), stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter last name: ");
    fgets(last_name, sizeof(last_name), stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    register_user(username, password, first_name, last_name, email);

    return 0;
}


To compile and run this code, you will need to have OpenSSL installed on your system. You can compile it using:


gcc -o registration registration.c -lcrypto
./registration