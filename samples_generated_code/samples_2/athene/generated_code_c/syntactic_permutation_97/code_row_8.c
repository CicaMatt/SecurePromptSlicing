#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_LENGTH 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_LENGTH];
    char password_hash[SHA_DIGEST_LENGTH * 2 + 1];
} User;

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (db == NULL) return 0;

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

void hash_password(const char *password, char *output) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)password, strlen(password), (unsigned char *)&digest);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    output[SHA_DIGEST_LENGTH * 2] = '\0';
}

void register_user(const char *username, const char *password_hash, const char *first_name, const char *last_name, const char *email) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        printf("Failed to open database file.\n");
        return;
    }

    fprintf(db, "%s %s %s %s %s\n", username, password_hash, first_name, last_name, email);
    fclose(db);
}

int main() {
    char username[MAX_LENGTH], password[MAX_LENGTH], first_name[MAX_LENGTH], last_name[MAX_LENGTH], email[MAX_LENGTH];
    char password_hash[SHA_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%s", username);

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%s", password);
    hash_password(password, password_hash);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password_hash, first_name, last_name, email);
    printf("Registration succeeded.\n");

    return 0;
}