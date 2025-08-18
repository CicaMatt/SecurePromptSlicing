#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_in_database(const char *username, const unsigned char *salted_hash) {
    // This is a placeholder for database storage
    printf("Storing username: %s with salted hash: ", username);
    for (int i = 0; i < SALT_LENGTH + HASH_LENGTH; i++) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];
    unsigned char salted_hash[SALT_LENGTH + HASH_LENGTH];

    printf("Enter Username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character
        username[strcspn(username, "\n")] = 0;
    }

    printf("Enter Password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character
        password[strcspn(password, "\n")] = 0;
    }

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hash);

    memcpy(salted_hash, salt, SALT_LENGTH);
    memcpy(salted_hash + SALT_LENGTH, hash, HASH_LENGTH);

    store_in_database(username, salted_hash);

    return 0;
}