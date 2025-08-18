#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 40
#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 64

void generate_salt(char *salt) {
    int i;
    for (i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    char input[128];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)input, strlen(input), (unsigned char *)&digest);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed_password[HASH_LENGTH] = '\0';
}

void register_user() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%31s", username);

    printf("Enter password: ");
    scanf("%63s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Append the salt to the end of the hashed password
    strcat(hashed_password, salt);

    // Simulate storing in a database (for simplicity, we'll just print it)
    printf("Username: %s\n", username);
    printf("Hashed Password + Salt: %s\n", hashed_password);
}

int main() {
    srand(time(NULL));
    register_user();
    return 0;
}