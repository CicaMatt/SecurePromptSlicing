#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hashing function to encrypt the password
char *hash(char *password) {
    char *output;
    // TODO: Use a hashing algorithm of your choice to hash the password

    return output;
}

int main() {
    char username[100];
    char password[100];
    char *hashed_password;

    // Get user input for username and password
    printf("Username: ");
    scanf("%s", &username);
    printf("Password: ");
    scanf("%s", &password);

    hashed_password = hash(password);

    // TODO: Save the username and encrypted password to a file or database.

    return 0;
}