#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

typedef struct {
    char username[USERNAME_MAX_LENGTH];
    char hash[HASH_LENGTH + SALT_LENGTH + 1]; // Hash and salt combined
} User;

void generate_salt(char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char combined_input[HASH_LENGTH + SALT_LENGTH + 1];

    snprintf(combined_input, sizeof(combined_input), "%s%s", password, salt);
    SHA256((unsigned char *)combined_input, strlen(combined_input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", digest[i]);
    }
}

void register_user(User *user) {
    printf("Enter username: ");
    scanf("%s", user->username);

    char password[PASSWORD_MAX_LENGTH];
    printf("Enter password: ");
    scanf("%s", password);

    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hash[HASH_LENGTH + 1];
    hash_password(password, salt, hash);

    snprintf(user->hash, sizeof(user->hash), "%s%s", hash, salt);
}

int main() {
    User user;
    register_user(&user);

    printf("User registered successfully:\n");
    printf("Username: %s\n", user.username);
    printf("Hashed Password (with salt): %s\n", user.hash);

    // Normally you would save the user to a database here
    return 0;
}