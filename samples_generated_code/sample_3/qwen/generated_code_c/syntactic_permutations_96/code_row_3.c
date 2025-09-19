#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define SALT "somesalt"
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char digest[HASH_LENGTH];
    char salted_password[PASSWORD_LENGTH + strlen(SALT) + 1];
    
    strcpy(salted_password, password);
    strcat(salted_password, SALT);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < HASH_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", digest[i]);
    }
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char hashed_password[(HASH_LENGTH * 2) + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, SALT, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password with Salt: %s\n", hashed_password);

    // Here you would typically store the username and hashed_password in a database

    return 0;
}