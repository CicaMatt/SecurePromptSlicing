#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USER 100
#define DB_FILE "users.txt"

typedef struct {
    char username[50];
    char password[65]; // SHA-256 hash length + null terminator
} User;

int user_exists(const char *username) {
    FILE *file = fopen(DB_FILE, "r");
    if (!file) return 0;

    User user;
    while (fscanf(file, "%49s %64s", user.username, user.password) == 2) {
        if (strcmp(user.username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    FILE *file = fopen(DB_FILE, "a");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char hashed_password[65];
    hash_password(password, hashed_password);

    fprintf(file, "%s %s %s %s %s\n", username, hashed_password, first_name, last_name, email);
    fclose(file);
    printf("Registration succeeded.\n");
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    register_user(username, password, first_name, last_name, email);
    return 0;
}