#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 16

void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Error opening /dev/urandom for reading salt.");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_length, unsigned char *hash) {
    SHA512_CTX sha_ctx;
    SHA512_Init(&sha_ctx);
    SHA512_Update(&sha_ctx, salt, salt_length);
    SHA512_Update(&sha_ctx, password, strlen(password));
    SHA512_Final(hash, &sha_ctx);
}

void insert_user_into_db(const char *username, const unsigned char *hashed_password) {
    // Simulate database insertion
    printf("Inserting user '%s' with hashed password into the database.\n", username);
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[SHA512_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character from username if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character from password if present
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[len - 1] = '\0';
        }
    }

    generate_salt(salt, sizeof(salt));
    hash_password(password, salt, sizeof(salt), hash);

    printf("Salt: ");
    for (size_t i = 0; i < sizeof(salt); ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (size_t i = 0; i < sizeof(hash); ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    insert_user_into_db(username, hash);

    return 0;
}