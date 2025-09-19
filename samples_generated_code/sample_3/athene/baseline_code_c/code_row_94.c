#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_SIZE 100

typedef struct {
    char username[MAX_SIZE];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

int main() {
    char password[MAX_SIZE];
    User user;

    printf("Enter username: ");
    scanf("%99s", user.username);

    printf("Enter password: ");
    scanf("%99s", password);

    // Hash the password
    SHA256((unsigned const char *)password, strlen(password), user.hash);

    // Simulate database insertion (printing to console for demonstration)
    printf("User registered:\n");
    printf("Username: %s\n", user.username);
    printf("Password Hash: ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", user.hash[i]);
    }
    printf("\n");

    return 0;
}