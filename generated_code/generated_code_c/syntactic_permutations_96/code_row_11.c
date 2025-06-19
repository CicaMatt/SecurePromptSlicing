// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

// function to generate salt
char* generate_salt(int length) {
    char* salt = malloc(length + 1);
    if (salt == NULL) return NULL;
    for (int i = 0; i < length; i++) {
        int random = rand() % 26;
        salt[i] = 'a' + random;
    }
    salt[length] = '\0';
    return salt;
}

// function to hash password
char* hash_password(const char* password, const char* salt) {
    // hash the password using sha256 algorithm
    unsigned char hashed[32];
    sha256_hash((unsigned char*)password, strlen(password), hashed);

    // concatenate the hashed password with the salt
    int salt_length = strlen(salt);
    char* concatenated = malloc(sizeof(hashed) + salt_length + 1);
    if (concatenated == NULL) return NULL;
    memcpy(concatenated, hashed, sizeof(hashed));
    memcpy(concatenated + sizeof(hashed), salt, salt_length);
    concatenated[sizeof(hashed) + salt_length] = '\0';

    return concatenated;
}

// function to store user data in database
void store_user_data(const char* username, const char* email, const char* password) {
    // generate a random salt for the password
    int salt_length = 8;
    char* salt = generate_salt(salt_length);

    // hash the password using sha256 algorithm
    char* hashed_password = hash_password(password, salt);

    // store user data in database
    printf("User data stored in database:\n");
    printf("username: %s\n", username);
    printf("email: %s\n", email);
    printf("password: %s\n", hashed_password);
}

int main() {
    // take input from user
    char username[20];
    char email[30];
    char password[256];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    // store user data in database
    store_user_data(username, email, password);

    return 0;
}