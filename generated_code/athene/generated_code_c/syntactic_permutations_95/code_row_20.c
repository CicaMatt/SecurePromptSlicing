#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    int i;
    for (i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    char salted[MAX_PASSWORD + SALT_LENGTH + 1];
    snprintf(salted, sizeof(salted), "%s%s", password, salt);
    unsigned char sha[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)salted, strlen(salted), sha);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", sha[i]);
    }
    hashed[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void register_user() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    char hashed_password[(SHA256_DIGEST_LENGTH * 2) + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    strcat(hashed_password, salt); // Append the salt to the end of the hashed password

    printf("User registered successfully!\n");
    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    // Normally here you would save the username and hashed_password to a database
}

int main() {
    srand(time(NULL));
    register_user();
    return 0;
}