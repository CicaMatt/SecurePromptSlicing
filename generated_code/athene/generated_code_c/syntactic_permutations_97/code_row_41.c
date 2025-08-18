#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_LEN 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_LEN];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (!db) return 0;

    User user;
    while (fread(&user, sizeof(User), 1, db)) {
        if (strcmp(user.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }

    fclose(db);
    return 0;
}

int register_user(const char *username, const char *password_hash, const char *first_name, const char *last_name, const char *email) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return -1;

    User user;
    strncpy(user.username, username, MAX_LEN);
    strncpy(user.password_hash, password_hash, SHA256_DIGEST_LENGTH * 2 + 1);

    fwrite(&user, sizeof(User), 1, db);
    fclose(db);
    return 0;
}

int main() {
    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%99s", password);
    hash_password(password, password_hash);

    printf("Enter first name: ");
    scanf("%99s", first_name);

    printf("Enter last name: ");
    scanf("%99s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(username, password_hash, first_name, last_name, email) == 0) {
        printf("Registration succeeded.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}