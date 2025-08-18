#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void hash_password(const char *password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    
    printf("Hashed Password (hex): ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}


To compile and run this code, you will need the OpenSSL library installed. You can typically install it using a package manager like `apt` on Ubuntu (`sudo apt-get install libssl-dev`) or `brew` on macOS (`brew install openssl`). Then compile with:


gcc -o registration_form registration_form.c -lssl -lcrypto
./registration_form


This program will prompt the user to enter a username and password, hash the password using SHA-256, and then print both the username and the hashed password in hexadecimal format.