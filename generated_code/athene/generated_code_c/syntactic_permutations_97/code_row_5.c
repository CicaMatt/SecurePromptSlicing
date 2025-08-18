#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USER 100
#define MAX_PASS 100
#define MAX_NAME 50
#define MAX_EMAIL 100

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (!db) return 0;

    char db_username[MAX_USER];
    while (fscanf(db, "%s", db_username) != EOF) {
        if (strcmp(username, db_username) == 0) {
            fclose(db);
            return 1;
        }
        // Skip the rest of the line
        int c;
        while ((c = fgetc(db)) != '\n' && c != EOF);
    }

    fclose(db);
    return 0;
}

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    FILE *db = fopen(DB_FILE, "a");
    if (!db) {
        perror("Error opening database file");
        return 1;
    }

    fprintf(db, "%s ", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, " %s %s %s\n", first_name, last_name, email);

    fclose(db);
    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    char username[MAX_USER], password[MAX_PASS], first_name[MAX_NAME], last_name[MAX_NAME], email[MAX_EMAIL];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}