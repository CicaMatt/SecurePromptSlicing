#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50
#define HASH_SIZE 65

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_SIZE - 1] = '\0';
}

int insert_into_database(const char *username, const char *password_hash) {
    // Simulate database insertion
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '%s');\n", username, password_hash);
    return 1; // Assume success for this example
}

int main() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    char password_hash[HASH_SIZE];

    printf("Enter username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_SIZE, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, password_hash);

    if (insert_into_database(username, password_hash)) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}