#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USER 50
#define MAX_PASS 100
#define MAX_NAME 50
#define MAX_EMAIL 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_USER];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

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

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void register_user(const User *new_user) {
    FILE *db = fopen(DB_FILE, "ab");
    if (!db) return;

    fwrite(new_user, sizeof(User), 1, db);
    fclose(db);
}

int main() {
    char username[MAX_USER], password[MAX_PASS], first_name[MAX_NAME], last_name[MAX_NAME], email[MAX_EMAIL];
    User new_user;

    printf("Enter username: ");
    scanf("%49s", username);

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%99s", password);
    hash_password(password, new_user.password_hash);

    printf("Enter first name: ");
    scanf("%49s", first_name);
    strcpy(new_user.username, username); // Copy username after checking existence

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    register_user(&new_user);
    printf("Registration succeeded.\n");

    return 0;
}