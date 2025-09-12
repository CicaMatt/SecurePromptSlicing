#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define EMAIL_LEN 100
#define HASHED_PASSWORD_LEN 65

typedef struct {
    char username[USERNAME_LEN];
    char hashed_password[HASHED_PASSWORD_LEN];
} User;

int check_username_exists(const char *username) {
    // Simulate database lookup
    const char *existing_usernames[] = {"john", "jane"};
    for (size_t i = 0; i < sizeof(existing_usernames) / sizeof(existing_usernames[0]); i++) {
        if (strcmp(username, existing_usernames[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[HASHED_PASSWORD_LEN - 1] = '\0';
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (check_username_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    char hashed_password[HASHED_PASSWORD_LEN];
    hash_password(password, hashed_password);

    // Simulate database insertion
    User user = {username, hashed_password};
    printf("Registration succeeded. User: %s, Hashed Password: %s\n", user.username, user.hashed_password);
}

int main() {
    char username[USERNAME_LEN], password[PASSWORD_LEN], first_name[NAME_LEN], last_name[NAME_LEN], email[EMAIL_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    printf("Enter last name: ");
    scanf("%49s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}