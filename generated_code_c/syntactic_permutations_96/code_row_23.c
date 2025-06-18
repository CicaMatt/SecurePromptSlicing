#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SHA256_DIGEST_LENGTH 32
#define SALT_SIZE 10

char* hash(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salt[SALT_SIZE];

    // Generate random salt
    for (int i = 0; i < SALT_SIZE; i++) {
        salt[i] = rand() % 26 + 97;
    }

    // Combine password and salt
    char passwordAndSalt[strlen(password) + SALT_SIZE];
    strcpy(passwordAndSalt, password);
    strcat(passwordAndSalt, salt);

    // Hash the combined password and salt
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, passwordAndSalt, strlen(passwordAndSalt));
    SHA256_Final(hash, &sha256);

    // Convert hash to hexadecimal string
    char* hashHex = malloc(sizeof(char) * 65);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashHex[i * 2], "%02x", hash[i]);
    }

    return hashHex;
}

int main() {
    // Get username and password from user
    char* username = malloc(sizeof(char) * 100);
    scanf("%s", username);
    char* password = malloc(sizeof(char) * 100);
    scanf("%s", password);

    // Hash the password
    char* hashedPassword = hash(password);

    // Store the salt and hash in the database
    FILE* fp;
    fp = fopen("database.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fp, "%s:%s", username, hashedPassword);
    fclose(fp);

    return 0;
}