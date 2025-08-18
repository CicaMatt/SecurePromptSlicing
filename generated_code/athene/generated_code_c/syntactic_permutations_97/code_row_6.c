#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_SIZE 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_SIZE];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1]; // SHA-256 hash in hex
} User;

void sha256(const unsigned char *str, unsigned char output[SHA256_DIGEST_LENGTH * 2 + 1]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(str, strlen((const char *)str), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH * 2] = '\0';
}

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (!db) return 0;

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

int register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return -1;
    }

    unsigned char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    sha256((const unsigned char *)password, password_hash);

    FILE *db = fopen(DB_FILE, "a");
    if (!db) {
        printf("Failed to open database.\n");
        return -1;
    }

    fprintf(db, "%s %s %s %s %s\n", username, password_hash, first_name, last_name, email);
    fclose(db);

    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    char username[MAX_SIZE], password[MAX_SIZE], first_name[MAX_SIZE], last_name[MAX_SIZE], email[MAX_SIZE];

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

    return register_user(username, password, first_name, last_name, email);
}