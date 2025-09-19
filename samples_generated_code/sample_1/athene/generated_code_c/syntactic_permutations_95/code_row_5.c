#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2)
#define USERNAME_MAX_LENGTH 100
#define PASSWORD_MAX_LENGTH 100

void generate_salt(char *salt, size_t length) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, length, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[USERNAME_MAX_LENGTH + SALT_LENGTH + 1];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256((unsigned char *)salted_password, strlen(salted_password), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
}

void register_user() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char salt[SALT_LENGTH];
    char hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    // Append the salt to the hashed password
    snprintf(hashed_password + HASH_LENGTH, SALT_LENGTH + 1, "%s", salt);

    printf("Registration successful.\n");
    printf("Stored in database: username=%s, hashed_password_salt=%s\n", username, hashed_password);
}

int main() {
    register_user();
    return 0;
}