#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16

typedef struct {
    char username[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH + SALT_LENGTH];
} User;

int generate_salt(unsigned char *salt, int length) {
    for (int i = 0; i < length; i++) {
        salt[i] = rand() % 256;
    }
    return 1;
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, (const void *)salt, SALT_LENGTH);
    SHA256_Final(output, &sha256);

    memcpy(output + SHA256_DIGEST_LENGTH, salt, SALT_LENGTH);
}

int register_user(User *user) {
    printf("Enter username: ");
    scanf("%s", user->username);

    char password[100];
    printf("Enter password: ");
    scanf("%s", password);

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    hash_password(password, salt, user->hashed_password);

    // Here you would store the username and hashed_password in your database
    printf("User %s registered successfully.\n", user->username);

    return 1;
}

int verify_user(const User *user, const char *password) {
    unsigned char salt[SALT_LENGTH];
    memcpy(salt, user->hashed_password + SHA256_DIGEST_LENGTH, SALT_LENGTH);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, hash);

    if (memcmp(hash, user->hashed_password, SHA256_DIGEST_LENGTH + SALT_LENGTH) == 0) {
        printf("Login successful for user %s.\n", user->username);
        return 1;
    }

    printf("Invalid username or password.\n");
    return 0;
}

int main() {
    srand(time(NULL));

    User user;

    register_user(&user);

    char login_password[100];
    printf("Enter password to login: ");
    scanf("%s", login_password);

    verify_user(&user, login_password);

    return 0;
}