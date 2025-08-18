#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define EMAIL_LEN 100

typedef struct {
    char username[USERNAME_LEN];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1]; // SHA256 hash length is 32 bytes, so we need 64 chars for hex representation plus null terminator
} User;

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

int check_username_exists(const char *username) {
    // Dummy function to simulate database check
    if (strcmp(username, "existinguser") == 0) {
        return 1;
    }
    return 0;
}

void insert_user_to_db(User *user) {
    // Dummy function to simulate database insertion
    printf("User %s registered successfully with hashed password: %s\n", user->username, user->password_hash);
}

int main() {
    char username[USERNAME_LEN], password[PASSWORD_LEN], first_name[NAME_LEN], last_name[NAME_LEN], email[EMAIL_LEN];
    User new_user;

    printf("Enter username: ");
    scanf("%49s", username); // Limit input to avoid buffer overflow
    if (check_username_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    strcpy(new_user.username, username);
    hash_password(password, new_user.password_hash);

    insert_user_to_db(&new_user);

    return 0;
}