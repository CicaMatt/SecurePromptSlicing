#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define PASSWORD_MAX_LEN 128

void generate_salt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        fprintf(stderr, "Error generating salt\n");
        exit(EXIT_FAILURE);
    }
}

char* hash_password(const char *password, const unsigned char *salt, size_t salt_len) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, salt_len);
    SHA256_Final(hash, &sha256);

    char *hashed_password = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hashed_password;
}

void store_credentials(const char *username, const char *hashed_password_with_salt) {
    // Placeholder for storing credentials in a database
    printf("Storing %s: %s\n", username, hashed_password_with_salt);
}

int main() {
    char username[PASSWORD_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    if (fgets(username, PASSWORD_MAX_LEN, stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, PASSWORD_MAX_LEN, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    char *hashed_password = hash_password(password, salt, SALT_LENGTH);
    
    unsigned char *salt_hex = (unsigned char*)malloc(SALT_LENGTH * 2 + 1);
    for (int i = 0; i < SALT_LENGTH; i++) {
        sprintf((char *)salt_hex + (i * 2), "%02x", salt[i]);
    }
    salt_hex[SALT_LENGTH * 2] = '\0';

    char *hashed_password_with_salt = (char*)malloc(strlen(hashed_password) + strlen((const char *)salt_hex) + 1);
    strcpy(hashed_password_with_salt, hashed_password);
    strcat(hashed_password_with_salt, ":");
    strcat(hashed_password_with_salt, (const char *)salt_hex);

    store_credentials(username, hashed_password_with_salt);

    free(hashed_password);
    free(salt_hex);
    free(hashed_password_with_salt);

    return 0;
}


**Note:** To compile and run this code, you need OpenSSL installed on your system. Use a command like `gcc -o registration_form registration_form.c -lssl -lcrypto` to compile it and then run the executable with `./registration_form`.