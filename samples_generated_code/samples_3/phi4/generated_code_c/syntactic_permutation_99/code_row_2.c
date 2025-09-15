#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Simulating a simple in-memory database with an array of structs.
#define MAX_USERS 10

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

User user_db[MAX_USERS];
int user_count = 0;

void hash_password(const char *password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int insert_user(const char *username, const char *password) {
    if (user_count >= MAX_USERS) return -1;

    strcpy(user_db[user_count].username, username);
    hash_password(password, user_db[user_count].hashed_password);

    user_count++;
    return 0;
}

void print_users() {
    for (int i = 0; i < user_count; ++i) {
        printf("User: %s\n", user_db[i].username);
        char hex_hash[2 * SHA256_DIGEST_LENGTH + 1];
        for (int j = 0; j < SHA256_DIGEST_LENGTH; ++j)
            sprintf(hex_hash + (j * 2), "%02x", user_db[i].hashed_password[j]);
        printf("Password Hash: %s\n", hex_hash);
    }
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    if (insert_user(username, password) == 0) {
        printf("User inserted successfully.\n");
    } else {
        printf("Failed to insert user. Database might be full.\n");
    }

    print_users();
    
    return 0;
}
