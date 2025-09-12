#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_SIZE 256

typedef struct {
    char username[MAX_SIZE];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[MAX_SIZE];
    char last_name[MAX_SIZE];
    char email[MAX_SIZE];
} User;

int check_username_exists(const char *username) {
    // Simulate a database check
    if (strcmp(username, "existinguser") == 0) {
        return 1;
    }
    return 0;
}

void hash_password(const char *password, char *output_hash) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_hash + (i * 2), "%02x", hash[i]);
    }
}

void insert_user(const User *user) {
    // Simulate inserting a user into the database
    printf("User registered successfully:\n");
    printf("Username: %s\n", user->username);
    printf("Password Hash: %s\n", user->password_hash);
    printf("First Name: %s\n", user->first_name);
    printf("Last Name: %s\n", user->last_name);
    printf("Email: %s\n", user->email);
}

int main() {
    User user;
    char password[MAX_SIZE];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%255s", user.username);

    if (check_username_exists(user.username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%255s", password);
    hash_password(password, password_hash);

    printf("Enter first name: ");
    scanf("%255s", user.first_name);

    printf("Enter last name: ");
    scanf("%255s", user.last_name);

    printf("Enter email: ");
    scanf("%255s", user.email);

    strcpy(user.password_hash, password_hash);
    insert_user(&user);
    return 0;
}