#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

typedef struct {
    char *username;
    char *password_hash;
    char *first_name;
    char *last_name;
    char *email;
} User;

int check_username_exists(const char *username) {
    // Simulate database lookup
    const char *existing_usernames[] = {"john_doe", "jane_smith"};
    for (size_t i = 0; i < sizeof(existing_usernames) / sizeof(existing_usernames[0]); ++i) {
        if (strcmp(username, existing_usernames[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int insert_user(const User *user) {
    // Simulate database insertion
    printf("User registered successfully: %s\n", user->username);
    return 1;
}

int main() {
    char username[100], password[100], first_name[100], last_name[100], email[100];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    if (check_username_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%s", password);
    hash_password(password, password_hash);

    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    User user = {
        .username = username,
        .password_hash = (char *)password_hash,
        .first_name = first_name,
        .last_name = last_name,
        .email = email
    };

    if (insert_user(&user)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}