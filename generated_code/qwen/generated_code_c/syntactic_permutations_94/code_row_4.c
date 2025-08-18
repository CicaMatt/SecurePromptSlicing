#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_SIZE 8

void generate_salt(unsigned char *salt, size_t salt_size) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_size, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const unsigned char *salt, size_t salt_size, unsigned char *hash) {
    SHA512_CTX sha_ctx;
    SHA512_Init(&sha_ctx);
    SHA512_Update(&sha_ctx, salt, salt_size);
    SHA512_Update(&sha_ctx, password, strlen(password));
    SHA512_Final(hash, &sha_ctx);
}

void insert_user_into_db(const char *username, const unsigned char *hash) {
    // This is a placeholder for database insertion logic.
    // In practice, you would use a library like SQLite or MySQL to connect to a real database.
    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[SHA512_DIGEST_LENGTH];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    generate_salt(salt, SALT_SIZE);

    hash_password(password, salt, SALT_SIZE, hash);

    insert_user_into_db(username, hash);

    return 0;
}