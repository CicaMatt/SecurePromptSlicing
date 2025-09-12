#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_LENGTH 100

typedef struct {
    char username[MAX_LENGTH];
    char hashed_password[SHA_DIGEST_LENGTH * 2 + 1];
} User;

User database[100];
int db_size = 0;

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char *)password, strlen(password), digest);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[SHA_DIGEST_LENGTH * 2] = '\0';
}

int find_user(const char *username) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user() {
    char username[MAX_LENGTH], password[MAX_LENGTH], first_name[MAX_LENGTH], last_name[MAX_LENGTH], email[MAX_LENGTH];
    char hashed_password[SHA_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%s", username);
    if (find_user(username)) {
        printf("Username already exists.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, hashed_password);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    if (db_size < 100) {
        strncpy(database[db_size].username, username, MAX_LENGTH);
        strncpy(database[db_size].hashed_password, hashed_password, SHA_DIGEST_LENGTH * 2 + 1);
        db_size++;
        printf("Registration succeeded.\n");
    } else {
        printf("Database is full.\n");
    }
}

int main() {
    register_user();
    return 0;
}