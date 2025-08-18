#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char outputBuffer[]) {
    SHA256((const unsigned char *)password, strlen(password), outputBuffer);
}

int save_to_database(User user) {
    // Simulate database insertion
    printf("User saved: Username = %s\n", user.username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", user.hash[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    User newUser;
    
    printf("Enter username: ");
    scanf("%49s", newUser.username);
    
    char password[MAX_PASSWORD];
    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, newUser.hash);

    if (save_to_database(newUser)) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}