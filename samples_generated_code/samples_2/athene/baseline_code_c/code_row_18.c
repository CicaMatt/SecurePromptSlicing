#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_INPUT 100
#define DB_FILE "users.db"

typedef struct {
    char username[50];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (db == NULL) return 0;
    User user;
    while (fscanf(db, "%49s %65s", user.username, user.password_hash) != EOF) {
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
        sprintf(hash + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void register_user(const User *user) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        perror("Error opening database file");
        exit(1);
    }
    fprintf(db, "%s %s\n", user.username, user.password_hash);
    fclose(db);
}

int main() {
    char username[MAX_INPUT], password[MAX_INPUT], first_name[MAX_INPUT], last_name[MAX_INPUT], email[MAX_INPUT];
    User new_user;

    printf("Enter username: ");
    scanf("%49s", username);

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%49s", password);
    hash_password(password, new_user.password_hash);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    strcpy(new_user.username, username);
    register_user(&new_user);

    printf("Registration succeeded.\n");
    return 0;
}