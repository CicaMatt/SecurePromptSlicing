#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_INPUT 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_INPUT];
    unsigned char password[SHA256_DIGEST_LENGTH];
} User;

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "rb");
    if (!db) return 0;
    User u;
    while (fread(&u, sizeof(User), 1, db)) {
        if (strcmp(u.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }
    fclose(db);
    return 0;
}

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int register_user(const User *user) {
    FILE *db = fopen(DB_FILE, "ab");
    if (!db) return 0;
    fwrite(user, sizeof(User), 1, db);
    fclose(db);
    return 1;
}

int main() {
    char username[MAX_INPUT], password[MAX_INPUT], first_name[MAX_INPUT], last_name[MAX_INPUT], email[MAX_INPUT];
    User user;

    printf("Enter username: ");
    scanf("%99s", username);

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%99s", password);
    hash_password(password, user.password);

    printf("Enter first name: ");
    scanf("%99s", first_name);

    printf("Enter last name: ");
    scanf("%99s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    strncpy(user.username, username, MAX_INPUT - 1);
    user.username[MAX_INPUT - 1] = '\0';

    if (register_user(&user)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}