#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_LINE 1024

typedef struct {
    char username[50];
    char password_hash[65]; // SHA-256 hash + null terminator
    char first_name[50];
    char last_name[50];
    char email[100];
} User;

void sha256(const char *str, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(outputBuffer, &sha256);
}

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (!db) return 0;

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, db)) {
        User u;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", u.username, u.password_hash, u.first_name, u.last_name, u.email);
        if (strcmp(u.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }

    fclose(db);
    return 0;
}

void save_user(const User *user) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) {
        printf("Failed to open database file.\n");
        exit(1);
    }

    fprintf(db, "%s|%s|%s|%s|%s\n", user->username, user->password_hash, user->first_name, user->last_name, user->email);
    fclose(db);
}

int main() {
    User new_user;
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", new_user.username);

    if (user_exists(new_user.username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%49s", new_user.password_hash);
    sha256(new_user.password_hash, password_hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&new_user.password_hash[i * 2], "%02x", (unsigned int)password_hash[i]);
    }

    printf("Enter first name: ");
    scanf("%49s", new_user.first_name);

    printf("Enter last name: ");
    scanf("%49s", new_user.last_name);

    printf("Enter email: ");
    scanf("%99s", new_user.email);

    save_user(&new_user);
    printf("Registration succeeded.\n");
    return 0;
}