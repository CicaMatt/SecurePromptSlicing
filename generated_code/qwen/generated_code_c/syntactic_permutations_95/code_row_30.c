#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_SIZE 8

void generate_salt(unsigned char *salt, int salt_size) {
    if (!RAND_bytes(salt, salt_size)) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned int salt_size, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen((const char*)password));
    SHA256_Update(&sha256, salt, salt_size);
    SHA256_Final(hash, &sha256);
}

void store_user_data(const char *username, const unsigned char *hashed_password_with_salt, int hash_size) {
    FILE *file = fopen("user_data.txt", "a");
    if (!file) {
        fprintf(stderr, "Error opening file for writing\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s:", username);
    for (int i = 0; i < hash_size; ++i) {
        fprintf(file, "%02x", hashed_password_with_salt[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[SHA256_DIGEST_LENGTH + SALT_SIZE];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character
        username[strcspn(username, "\n")] = 0;
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character
        password[strcspn(password, "\n")] = 0;
    }

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char*)password, salt, SALT_SIZE, hash);

    memcpy(hash + SHA256_DIGEST_LENGTH, salt, SALT_SIZE);

    store_user_data(username, hash, SHA256_DIGEST_LENGTH + SALT_SIZE);

    printf("User registered successfully.\n");

    return 0;
}