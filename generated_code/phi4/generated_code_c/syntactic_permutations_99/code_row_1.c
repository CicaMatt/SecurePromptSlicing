#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Dummy function to represent inserting data into a database.
int insert_into_database(const char *username, const unsigned char hash[SHA256_DIGEST_LENGTH]) {
    printf("Inserting username: %s\n", username);
    printf("Hashed password (hex): ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 1; // Success
}

void get_input(char *buffer, int length) {
    if(fgets(buffer, length, stdin)) {
        size_t len = strlen(buffer);
        if(len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        exit(1);
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter username: ");
    get_input(username, sizeof(username));

    printf("Enter password: ");
    get_input(password, sizeof(password));

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    if (insert_into_database(username, hash)) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
    }

    return 0;
}


To compile and run this code, you need OpenSSL development libraries installed on your system. Use the following command for compilation:


gcc -o hash_password hash_password.c -lssl -lcrypto
./hash_password