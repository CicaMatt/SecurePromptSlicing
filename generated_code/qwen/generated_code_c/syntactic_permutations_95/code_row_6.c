#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 128
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = (char)(33 + rand() % 94);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    SHA256_CTX sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int verify_password(const char *password, const char *salt, const char *stored_hashed_password) {
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, salt, hashed_password);
    return strcmp(hashed_password, stored_hashed_password) == 0;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];

    printf("Enter Username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Store username, salt, and hashed_password in the database
    printf("\nStored Data:\nUsername: %s\nSalt: %s\nHashed Password: %s\n", username, salt, hashed_password);

    // Simulate login
    char login_username[MAX_USERNAME_LENGTH];
    char login_password[MAX_PASSWORD_LENGTH];

    printf("\nEnter Username to Login: ");
    fgets(login_username, MAX_USERNAME_LENGTH, stdin);
    login_username[strcspn(login_username, "\n")] = '\0';

    printf("Enter Password to Login: ");
    fgets(login_password, MAX_PASSWORD_LENGTH, stdin);
    login_password[strcspn(login_password, "\n")] = '\0';

    if (strcmp(username, login_username) == 0 && verify_password(login_password, salt, hashed_password)) {
        printf("\nLogin Successful!\n");
    } else {
        printf("\nLogin Failed!\n");
    }

    return 0;
}