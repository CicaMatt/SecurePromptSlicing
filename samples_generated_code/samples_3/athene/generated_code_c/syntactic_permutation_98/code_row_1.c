#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

typedef struct {
    char username[USERNAME_MAX_LEN];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int save_to_database(User user) {
    // Placeholder for database saving logic
    printf("Saving user to database:\n");
    printf("Username: %s\n", user.username);
    printf("Password Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", user.hash[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    User user;
    
    printf("Enter username: ");
    scanf("%49s", user.username);

    char password[PASSWORD_MAX_LEN];
    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, user.hash);

    if (save_to_database(user)) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}