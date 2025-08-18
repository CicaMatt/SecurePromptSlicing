#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>

#define MAX_USERNAME 32
#define MAX_PASSWORD 64
#define SALT_LENGTH 10

void generate_salt(char *salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    for (int i = 0; i < SALT_LENGTH - 1; ++i) {
        int key = rand() % (sizeof(charset) - 1);
        salt[i] = charset[key];
    }
    salt[SALT_LENGTH - 1] = '\0';
}

void register_user(const char *username, const char *password) {
    char salt[SALT_LENGTH];
    generate_salt(salt);
    char *hashed_password = crypt(password, salt);

    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salted Hashed Password: %s\n", hashed_password);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username (max %d chars): ", MAX_USERNAME - 1);
    if (!fgets(username, sizeof(username), stdin)) return 1;
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password (max %d chars): ", MAX_PASSWORD - 1);
    if (!fgets(password, sizeof(password), stdin)) return 1;
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    register_user(username, password);

    return 0;
}