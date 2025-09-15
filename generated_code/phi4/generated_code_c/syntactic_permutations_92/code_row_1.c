#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_INPUT 256

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_INPUT, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_INPUT, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}
