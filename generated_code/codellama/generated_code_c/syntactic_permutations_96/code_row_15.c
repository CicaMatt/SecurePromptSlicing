#include <stdio.h>
#include <stdlib.h>
#include "sha256.h"

char* sha256(const char* input) {
    // Generate salt using a function
    char* salt = generate_salt();

    // Concatenate the salt with the hashed password
    char* hashed_password = sha256_hash((input + salt), strlen(input));

    return hashed_password;
}

int main() {
    // Username and password input
    char username[30];
    char password[30];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    // Hash the password using SHA-256
    char* hashed_password = sha256(password);

    // Store the hashed password in the database
    store_in_db(username, hashed_password);

    return 0;
}