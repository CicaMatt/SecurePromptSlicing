#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USER 256
#define MAX_PASS 256
#define MAX_NAME 128
#define MAX_EMAIL 256
#define HASH_LENGTH 40

typedef struct {
    char username[MAX_USER];
    char password_hash[HASH_LENGTH];
} User;

User users[] = {{"user1", "hashedpass1"}, {"user2", "hashedpass2"}};
int user_count = 2;

char *hash_password(const char *password) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *) password, strlen(password), hash);
    static char buffer[HASH_LENGTH + 1];
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(buffer + (i * 2), "%02x", (unsigned int)hash[i]);
    }
    buffer[HASH_LENGTH] = '\0';
    return buffer;
}

int user_exists(const char *username) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(char *username, char *password, char *first_name, char *last_name, char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    User new_user;
    strncpy(new_user.username, username, MAX_USER - 1);
    strcpy(new_user.password_hash, hash_password(password));
    users[user_count] = new_user;
    user_count++;

    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

    printf("Enter username: ");
    fgets(username, MAX_USER, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, MAX_PASS, stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter first name: ");
    fgets(first_name, MAX_NAME, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter last name: ");
    fgets(last_name, MAX_NAME, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strcspn(email, "\n")] = 0;

    register_user(username, password, first_name, last_name, email);

    return 0;
}