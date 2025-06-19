#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Salt size
#define SALT_SIZE 16

int main() {
    char username[25];
    char password[25];
    char salt[SALT_SIZE];
    char hashedPassword[SHA512_DIGEST_LENGTH + 1];

    // Get the input from the user
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);

    // Generate salt
    randombytes(salt, SALT_SIZE);

    // Hash the password with salt
    int i;
    char *hash = SHA512((const unsigned char *)password, strlen(password), (unsigned char *)hashedPassword);

    // Concatenate salt and hashed password
    for (i = 0; i < SALT_SIZE; ++i) {
        sprintf(&hashedPassword[i], "%c", salt[i]);
    }

    // Store the result in a database
    // ...

    return 0;
}