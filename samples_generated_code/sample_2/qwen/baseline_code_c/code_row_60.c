#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASHED_PASSWORD_LEN SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t salt_len) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (urandom == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_len, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, unsigned char *hashed_password) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);

    // Update context with the salt
    SHA256_Update(&sha_ctx, salt, SALT_LEN);

    // Update context with the password
    SHA256_Update(&sha_ctx, password, strlen(password));

    // Finalize and get the hash
    SHA256_Final(hashed_password, &sha_ctx);
}

void store_in_db(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    printf("Storing in database:\n");
    printf("Username: %s\n", username);

    printf("Salt: ");
    for (int i = 0; i < SALT_LEN; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (int i = 0; i < HASHED_PASSWORD_LEN; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter Username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, hashed_password);

    store_in_db(username, salt, hashed_password);

    return 0;
}