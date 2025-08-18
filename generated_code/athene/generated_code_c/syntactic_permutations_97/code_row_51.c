#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_NAME 50
#define MAX_EMAIL 100

typedef struct {
    char username[MAX_USERNAME];
    char password[65]; // SHA-256 hash is 64 chars + null terminator
} User;

User users[100]; // Assuming a max of 100 users for simplicity
int user_count = 0;

void hash_password(const char *password, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed[64] = '\0'; // Null terminate the string
}

int check_username_exists(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (check_username_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    if (user_count >= 100) {
        printf("User limit reached.\n");
        return;
    }

    User new_user;
    strncpy(new_user.username, username, MAX_USERNAME);
    char hashed_password[65];
    hash_password(password, hashed_password);
    strncpy(new_user.password, hashed_password, 65);

    // For simplicity, we are not storing first name, last name, and email in the struct
    // In a real application, you would store these fields as well

    users[user_count++] = new_user;
    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

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

    register_user(username, password, first_name, last_name, email);

    return 0;
}