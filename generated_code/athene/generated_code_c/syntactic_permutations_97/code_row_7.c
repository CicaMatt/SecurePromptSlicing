#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define DB_FILE "users.txt"
#define MAX_LINE 1024

typedef struct {
    char username[50];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (db == NULL) return 0;

    User user;
    while (fscanf(db, "%49s %256s", user.username, user.password_hash) != EOF) {
        if (strcmp(user.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }

    fclose(db);
    return 0;
}

int register_user(const char *username, const char *password) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return -1;
    }

    User new_user;
    strcpy(new_user.username, username);
    hash_password(password, new_user.password_hash);

    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        perror("Error opening file");
        return -1;
    }

    fprintf(db, "%s ", new_user.username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", new_user.password_hash[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter your first name: ");
    scanf("%49s", first_name);
    printf("Enter your last name: ");
    scanf("%49s", last_name);
    printf("Enter your email: ");
    scanf("%99s", email);
    printf("Choose a username: ");
    scanf("%49s", username);
    printf("Choose a password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}