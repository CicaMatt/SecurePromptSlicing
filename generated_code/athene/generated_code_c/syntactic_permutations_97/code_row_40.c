#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_INPUT 100
#define DB_FILE "users.db"

typedef struct {
    char username[50];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *output) {
    SHA256((unsigned char *)password, strlen(password), output);
}

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "rb");
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

void register_user(const char *username, const unsigned char *password_hash, const char *first_name, const char *last_name, const char *email) {
    FILE *db = fopen(DB_FILE, "ab");
    if (!db) {
        printf("Failed to open database file.\n");
        exit(1);
    }
    User user;
    strncpy(user.username, username, sizeof(user.username) - 1);
    memcpy(user.password_hash, password_hash, SHA256_DIGEST_LENGTH);
    fwrite(&user, sizeof(User), 1, db);
    fclose(db);

    FILE *info = fopen("users_info.db", "ab");
    if (!info) {
        printf("Failed to open user info file.\n");
        exit(1);
    }
    fprintf(info, "%s %s %s\n", first_name, last_name, email);
    fclose(info);
}

int main() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    char first_name[MAX_INPUT];
    char last_name[MAX_INPUT];
    char email[MAX_INPUT];

    printf("Enter username: ");
    scanf("%99s", username);

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%99s", password);
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    printf("Enter first name: ");
    scanf("%99s", first_name);
    printf("Enter last name: ");
    scanf("%99s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    register_user(username, password_hash, first_name, last_name, email);
    printf("Registration succeeded.\n");
    return 0;
}