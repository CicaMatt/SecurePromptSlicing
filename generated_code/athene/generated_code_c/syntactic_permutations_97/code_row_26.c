#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_INPUT 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_INPUT];
    char password[SHA256_DIGEST_LENGTH * 2 + 1];
    char firstname[MAX_INPUT];
    char lastname[MAX_INPUT];
    char email[MAX_INPUT];
} User;

void hash_password(const char *password, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
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

int register_user(const char *username, const char *password, const char *firstname, const char *lastname, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return -1;
    }

    User new_user = {0};
    strncpy(new_user.username, username, MAX_INPUT - 1);
    hash_password(password, new_user.password);
    strncpy(new_user.firstname, firstname, MAX_INPUT - 1);
    strncpy(new_user.lastname, lastname, MAX_INPUT - 1);
    strncpy(new_user.email, email, MAX_INPUT - 1);

    FILE *db = fopen(DB_FILE, "a");
    if (!db) {
        printf("Failed to open database file.\n");
        return -2;
    }

    fwrite(&new_user, sizeof(User), 1, db);
    fclose(db);

    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    char username[MAX_INPUT], password[MAX_INPUT], firstname[MAX_INPUT], lastname[MAX_INPUT], email[MAX_INPUT];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);
    printf("Enter first name: ");
    scanf("%99s", firstname);
    printf("Enter last name: ");
    scanf("%99s", lastname);
    printf("Enter email: ");
    scanf("%99s", email);

    register_user(username, password, firstname, lastname, email);

    return 0;
}