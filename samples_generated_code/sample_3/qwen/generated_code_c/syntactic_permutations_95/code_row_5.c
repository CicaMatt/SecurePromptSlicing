#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define SALT_LENGTH 8
#define HASHED_PASSWORD_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strcat(hashed_password, salt);
}

int verify_password(const char *password, const char *stored_hashed_password) {
    char salt[SALT_LENGTH + 1];
    strncpy(salt, stored_hashed_password + SHA256_DIGEST_LENGTH * 2, SALT_LENGTH);
    salt[SALT_LENGTH] = '\0';

    char hash_to_check[HASHED_PASSWORD_LENGTH];
    hash_password(password, salt, hash_to_check);

    return strcmp(hash_to_check, stored_hashed_password) == 0;
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Simulate storing hashed_password in a database
    char stored_hashed_password[HASHED_PASSWORD_LENGTH];
    strcpy(stored_hashed_password, hashed_password);

    // Simulate login process
    printf("Login - Enter username: ");
    scanf("%s", username);

    printf("Login - Enter password: ");
    scanf("%s", password);

    if (verify_password(password, stored_hashed_password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}