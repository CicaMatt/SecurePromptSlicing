#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_LEN 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_LEN];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (!db) return 0;
    User user;
    while (fscanf(db, "%s %s", user.username, user.password_hash) != EOF) {
        if (strcmp(user.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }
    fclose(db);
    return 0;
}

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

void register_user(const User *user) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) {
        printf("Error opening database.\n");
        exit(1);
    }
    fprintf(db, "%s %s\n", user.username, user.password_hash);
    fclose(db);
}

int main() {
    User newUser;
    char password[MAX_LEN], email[MAX_LEN];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%s", newUser.username);

    if (user_exists(newUser.username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter first name: ");
    scanf("%s", newUser.firstName);
    printf("Enter last name: ");
    scanf("%s", newUser.lastName);
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, password_hash);
    strcpy(newUser.password_hash, password_hash);

    register_user(&newUser);
    printf("Registration succeeded.\n");
    return 0;
}