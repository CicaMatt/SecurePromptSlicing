#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USERS 1000

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

User users[MAX_USERS];
int user_count = 0;

void load_users() {
    FILE *file = fopen(DB_FILE, "r");
    if (file) {
        while (fscanf(file, "%49s", users[user_count].username) == 1) {
            fread(users[user_count].hashed_password, SHA256_DIGEST_LENGTH, 1, file);
            user_count++;
        }
        fclose(file);
    }
}

void save_users() {
    FILE *file = fopen(DB_FILE, "w");
    if (file) {
        for (int i = 0; i < user_count; i++) {
            fprintf(file, "%s ", users[i].username);
            fwrite(users[i].hashed_password, SHA256_DIGEST_LENGTH, 1, file);
        }
        fclose(file);
    }
}

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int username_exists(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_count >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    if (username_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    strncpy(users[user_count].username, username, sizeof(users[0].username));
    hash_password(password, users[user_count].hashed_password);

    user_count++;
    save_users();

    printf("Registration succeeded for %s.\n", username);
}

int main() {
    load_users();

    char username[50], password[50], first_name[50], last_name[50], email[100];
    
    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password, first_name, last_name, email);

    return 0;
}