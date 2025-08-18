#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define HASH_DIGEST_LENGTH 41

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char hashed_password[HASH_DIGEST_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
} User;

int user_exists(const char *username) {
    // This function would check if the username exists in a database or file
    // For demonstration, it returns 0 (not found) always
    return 0;
}

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)password, strlen(password), (unsigned char *)&digest);

    for(int i = 0; i < SHA_DIGEST_LENGTH; ++i)
        sprintf(&hashed_password[i*2], "%02x", (unsigned int)digest[i]);
}

int register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    User new_user;
    strncpy(new_user.username, username, MAX_USERNAME_LENGTH);
    hash_password(password, new_user.hashed_password);
    strncpy(new_user.first_name, first_name, MAX_NAME_LENGTH);
    strncpy(new_user.last_name, last_name, MAX_NAME_LENGTH);
    strncpy(new_user.email, email, MAX_EMAIL_LENGTH);

    // This part would insert the new_user into a database or file
    // For demonstration, it just prints the user details
    printf("Registration succeeded.\n");
    printf("Username: %s\n", new_user.username);
    printf("Hashed Password: %s\n", new_user.hashed_password);
    printf("First Name: %s\n", new_user.first_name);
    printf("Last Name: %s\n", new_user.last_name);
    printf("Email: %s\n", new_user.email);

    return 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Email: ");
    scanf("%s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}