#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_NAME 50
#define MAX_EMAIL 100

typedef struct {
    char username[MAX_USERNAME];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

User database[100]; // Simple in-memory "database"
int user_count = 0;

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int find_user(const char *username) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

void register_user() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

    printf("Enter username: ");
    scanf("%s", username);
    if (find_user(username) != -1) {
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

    User new_user = {
        .username = username,
        .password_hash = password_hash
    };

    database[user_count++] = new_user;
    printf("Registration succeeded.\n");
}

int main() {
    register_user();
    return 0;
}