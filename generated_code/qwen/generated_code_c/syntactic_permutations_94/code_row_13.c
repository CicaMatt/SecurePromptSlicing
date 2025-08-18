#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(unsigned char salt[SALT_LENGTH]) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, sizeof(char), SALT_LENGTH, urandom);
    fclose(urandom);
}

void hash_password(const char* password, const unsigned char salt[SALT_LENGTH], unsigned char hash[SHA256_DIGEST_LENGTH]) {
    unsigned char salted_password[MAX_PASSWORD_LENGTH + SALT_LENGTH];
    memcpy(salted_password, salt, SALT_LENGTH);
    strcpy((char*)salted_password + SALT_LENGTH, password);

    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salted_password, strlen(password) + SALT_LENGTH);
    SHA256_Final(hash, &sha_ctx);
}

void insert_into_database(const char* username, const unsigned char hash[SHA256_DIGEST_LENGTH], const unsigned char salt[SALT_LENGTH]) {
    // Dummy database insertion logic
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\nSalt: ");
    for (int i = 0; i < SALT_LENGTH; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin)) {
        // Remove newline character
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin)) {
        // Remove newline character
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, hash);

    insert_into_database(username, hash, salt);

    return 0;
}