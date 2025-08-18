#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void hashPassword(const char* input, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char*)input, strlen(input), outputBuffer);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);

    // Remove newline character from username if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);

    // Remove newline character from password if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    
    printf("Hashed Password: ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    return 0;
}