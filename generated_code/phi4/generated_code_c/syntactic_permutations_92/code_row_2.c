#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hashPassword(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter Username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    return 0;
}
