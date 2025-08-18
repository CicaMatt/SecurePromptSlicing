#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char hashed_password[MAX_PASSWORD_LEN + 6]; // Extra space for salt (5 chars) and null terminator
} User;

void generate_salt(char *salt, size_t len) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (len > sizeof(charset) - 1) {
        len = sizeof(charset) - 1;
    }
    for (size_t n = 0; n < len; n++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        salt[n] = charset[key];
    }
    salt[len] = '\0';
}

void hash_password_with_salt(const char *password, const char *salt, char *hashed_password) {
    strcpy(hashed_password, password); // Simplified hashing: just appending for demonstration
    strcat(hashed_password, "$");
    strcat(hashed_password, salt);
}

int store_user_in_database(User *user) {
    FILE *file = fopen("users.db", "a+");
    if (!file) return -1;

    fprintf(file, "%s:%s\n", user->username, user->hashed_password);

    fclose(file);
    return 0;
}

int main() {
    srand(time(NULL));

    User new_user;
    
    printf("Enter username: ");
    fgets(new_user.username, MAX_USERNAME_LEN, stdin);
    new_user.username[strcspn(new_user.username, "\n")] = '\0'; // Remove newline character

    char password[MAX_PASSWORD_LEN];
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    char salt[6];  // Salt length of 5 characters
    generate_salt(salt, sizeof(salt) - 1);

    hash_password_with_salt(password, salt, new_user.hashed_password);

    if (store_user_in_database(&new_user) == 0) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to store user data in the database.\n");
    }

    return 0;
}