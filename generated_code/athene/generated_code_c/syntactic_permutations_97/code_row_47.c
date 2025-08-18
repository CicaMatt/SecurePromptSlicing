#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_INPUT 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_INPUT];
    char password[SHA_DIGEST_LENGTH * 2 + 1]; // SHA-256 hash length in hex
} User;

void sha256(const char *str, char outputBuffer[65]) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "r");
    if (!db) return 0;

    User user;
    while (fscanf(db, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(user.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }

    fclose(db);
    return 0;
}

int register_user(const char *username, const char *password, const char *firstName, const char *lastName, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return -1;
    }

    FILE *db = fopen(DB_FILE, "a");
    if (!db) {
        perror("Error opening database file");
        return -1;
    }

    char hashedPassword[65];
    sha256(password, hashedPassword);

    fprintf(db, "%s %s %s %s %s\n", username, hashedPassword, firstName, lastName, email);
    fclose(db);

    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    char username[MAX_INPUT], password[MAX_INPUT], firstName[MAX_INPUT], lastName[MAX_INPUT], email[MAX_INPUT];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", firstName);
    printf("Enter last name: ");
    scanf("%s", lastName);
    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password, firstName, lastName, email);

    return 0;
}