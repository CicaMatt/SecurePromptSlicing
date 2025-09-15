#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_BUFFER 256

typedef struct {
    char username[MAX_BUFFER];
    char password_hash[SHA256_DIGEST_LENGTH * 2 + 1]; // Hex string length for SHA-256 hash
    char first_name[MAX_BUFFER];
    char last_name[MAX_BUFFER];
    char email[MAX_BUFFER];
} User;

int db_has_user(const char* username) {
    // Simulate database lookup
    return 0; // Assume user does not exist in the database by default
}

void db_insert_user(User user) {
    printf("User %s inserted with hashed password: %s\n", user.username, user.password_hash);
}

void hash_password(const char* password, char* output_buffer) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(output_buffer + (i * 2), "%02x", digest[i]);
}

void register_user(const char* username, const char* password, const char* first_name,
                   const char* last_name, const char* email) {
    if (db_has_user(username)) {
        printf("Username %s already exists.\n", username);
    } else {
        User user;
        strncpy(user.username, username, MAX_BUFFER - 1);
        strncpy(user.first_name, first_name, MAX_BUFFER - 1);
        strncpy(user.last_name, last_name, MAX_BUFFER - 1);
        strncpy(user.email, email, MAX_BUFFER - 1);

        hash_password(password, user.password_hash);

        db_insert_user(user);
        printf("Registration succeeded for username: %s\n", username);
    }
}

int main() {
    char username[MAX_BUFFER], password[MAX_BUFFER], first_name[MAX_BUFFER],
         last_name[MAX_BUFFER], email[MAX_BUFFER];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    printf("Enter first name: ");
    scanf("%255s", first_name);

    printf("Enter last name: ");
    scanf("%255s", last_name);

    printf("Enter email: ");
    scanf("%255s", email);

    register_user(username, password, first_name, last_name, email);
    
    return 0;
}
