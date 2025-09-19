#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT "my_salt"
#define MAX_INPUT 256

void hashPassword(const char *password, unsigned char **output) {
    unsigned char salted_password[64];
    SHA256_CTX sha256;
    int i;

    // Concatenate the password and the salt
    strcpy((char *)salted_password, SALT);
    strcat((char *)salted_password, password);

    // Hash the result using SHA-256
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen((char *)salted_password));
    SHA256_Final(salted_password, &sha256);

    *output = malloc(SHA256_DIGEST_LENGTH);
    memcpy(*output, salted_password, SHA256_DIGEST_LENGTH);
}

int main() {
    char username[MAX_INPUT];
    char password[MAX_INPUT];

    // Prompt for user input
    printf("Enter username: ");
    fgets(username, MAX_INPUT, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_INPUT, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char *hashedPassword;

    // Hash the entered password
    hashPassword(password, &hashedPassword);

    // Simulate storing in a database (e.g., printing to console)
    printf("Storing user: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("\n");

    free(hashedPassword);

    return 0;
}
