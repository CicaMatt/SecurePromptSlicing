#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h> // For SHA256 hashing

#define USERNAME_MAX 100
#define PASSWORD_MAX 100
#define HASH_SIZE 64

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

void insert_into_database(const char *username, const char *password_hash) {
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, password_hash);
    // This is a placeholder for actual database insertion logic
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char password_hash[HASH_SIZE + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    hash_password(password, password_hash);

    insert_into_database(username, password_hash);

    return 0;
}