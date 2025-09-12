#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_INPUT 100
#define DB_FILE "users.txt"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int user_exists(const char *username) {
    FILE *file = fopen(DB_FILE, "r");
    if (!file) return 0;

    char line[MAX_INPUT];
    while (fgets(line, MAX_INPUT, file)) {
        char stored_username[MAX_INPUT];
        sscanf(line, "%s", stored_username);
        if (strcmp(stored_username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void register_user(const char *username, const unsigned char *password_hash, const char *first_name, const char *last_name, const char *email) {
    FILE *file = fopen(DB_FILE, "a");
    if (!file) {
        fprintf(stderr, "Error opening database file.\n");
        exit(1);
    }

    fprintf(file, "%s ", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(file, "%02x", password_hash[i]);
    }
    fprintf(file, " %s %s %s\n", first_name, last_name, email);

    fclose(file);
}

int main() {
    char username[MAX_INPUT], password[MAX_INPUT], first_name[MAX_INPUT], last_name[MAX_INPUT], email[MAX_INPUT];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

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

    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    hash_password(password, password_hash);
    register_user(username, password_hash, first_name, last_name, email);
    printf("Registration succeeded.\n");

    return 0;
}