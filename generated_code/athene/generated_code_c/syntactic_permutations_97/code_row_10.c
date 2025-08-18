#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_NAME 50
#define MAX_EMAIL 100

typedef struct {
    char username[MAX_USERNAME];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

User database[100];
int db_size = 0;

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int user_exists(const char *username) {
    for (int i = 0; i < db_size; i++) {
        if (strcmp(database[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

    printf("Enter username: ");
    scanf("%s", username);
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    strcpy(database[db_size].username, username);
    memcpy(database[db_size].password_hash, password_hash, SHA256_DIGEST_LENGTH);
    db_size++;

    printf("Registration succeeded.\n");
}

int main() {
    register_user();
    return 0;
}