#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char username[50];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int save_to_database(User user) {
    // Simulate database saving
    printf("Saving user: %s\n", user.username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", user.hash[i]);
    }
    printf("\n");
    return 1; // Return 1 for success, 0 for failure
}

int main() {
    User newUser;
    char password[50];

    printf("Enter username: ");
    scanf("%49s", newUser.username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, newUser.hash);

    if (save_to_database(newUser)) {
        printf("Registration successful.\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}