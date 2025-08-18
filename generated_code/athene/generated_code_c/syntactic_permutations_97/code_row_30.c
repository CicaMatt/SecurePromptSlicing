#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char hash[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

User database[100]; // Simple in-memory "database"
int user_count = 0;

void sha256(const char *str, char outputBuffer[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

int username_exists(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(database[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user() {
    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];
    char hash[65];

    printf("Enter username: ");
    scanf("%s", username);
    if (username_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", password);

    printf("Enter first name: ");
    scanf("%s", first_name);

    printf("Enter last name: ");
    scanf("%s", last_name);

    printf("Enter email: ");
    scanf("%s", email);

    sha256(password, hash);

    strcpy(database[user_count].username, username);
    strcpy(database[user_count].hash, hash);
    user_count++;

    printf("Registration succeeded.\n");
}

int main() {
    register_user();
    return 0;
}