#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define DB_SIZE 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 128
#define SALT_LEN 16

typedef struct {
    char username[USERNAME_LEN];
    unsigned char hashed_password[PASSWORD_LEN];
} User;

User database[DB_SIZE];
int user_count = 0;

void generate_salt(unsigned char salt[SALT_LEN]) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LEN; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const char *password, const unsigned char salt[SALT_LEN], unsigned char hashed_password[PASSWORD_LEN]) {
    SHA_CTX sha_ctx;
    SHA1_Init(&sha_ctx);
    SHA1_Update(&sha_ctx, password, strlen(password));
    SHA1_Update(&sha_ctx, salt, SALT_LEN);
    SHA1_Final(hashed_password, &sha_ctx);
}

int register_user(const char *username, const char *password) {
    if (user_count >= DB_SIZE) return 0;

    unsigned char salt[SALT_LEN];
    generate_salt(salt);

    hash_password(password, salt, database[user_count].hashed_password);

    strncpy(database[user_count].username, username, USERNAME_LEN - 1);
    database[user_count].username[USERNAME_LEN - 1] = '\0';

    for (int i = 0; i < SALT_LEN; ++i) {
        database[user_count].hashed_password[PASSWORD_LEN - SALT_LEN + i] = salt[i];
    }

    user_count++;
    return 1;
}

int verify_user(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0) {
            unsigned char salt[SALT_LEN];
            memcpy(salt, database[i].hashed_password + PASSWORD_LEN - SALT_LEN, SALT_LEN);

            unsigned char hashed_input[PASSWORD_LEN];
            hash_password(password, salt, hashed_input);

            if (memcmp(hashed_input, database[i].hashed_password, PASSWORD_LEN - SALT_LEN) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    char username[USERNAME_LEN], password[PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (register_user(username, password)) {
        printf("Registration successful.\n");

        printf("Verify login:\nEnter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (verify_user(username, password)) {
            printf("Login successful.\n");
        } else {
            printf("Login failed.\n");
        }
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}