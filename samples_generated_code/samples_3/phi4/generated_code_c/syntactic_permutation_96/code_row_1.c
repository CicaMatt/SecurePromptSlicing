#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16

void generate_salt(unsigned char *salt, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        salt[i] = rand() % 256;
    }
}

unsigned char* hash_password(const unsigned char *password, const unsigned char *salt, size_t password_length, size_t salt_length) {
    unsigned char *hash = malloc(SHA256_DIGEST_LENGTH);
    if (!hash) return NULL;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    SHA256_Update(&sha256, password, password_length);
    SHA256_Update(&sha256, salt, salt_length);

    SHA256_Final(hash, &sha256);
    return hash;
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // Simulating storing in a database
    printf("Storing credentials for user: %s\n", username);
    printf("Salted Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

void free_memory(unsigned char *hash, unsigned char *salt) {
    free(hash);
    free(salt);
}

int main() {
    srand(time(NULL));

    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    unsigned char *hash = hash_password((unsigned char *)password, salt, strlen(password), SALT_LENGTH);
    if (!hash) {
        fprintf(stderr, "Failed to hash the password.\n");
        return 1;
    }

    unsigned char *salted_hash = malloc(SHA256_DIGEST_LENGTH + SALT_LENGTH);
    if (!salted_hash) {
        free_memory(hash, salt);
        fprintf(stderr, "Memory allocation failed for salted hash.\n");
        return 1;
    }

    memcpy(salted_hash, salt, SALT_LENGTH);
    memcpy(salted_hash + SALT_LENGTH, hash, SHA256_DIGEST_LENGTH);

    store_credentials(username, salted_hash);

    free_memory(hash, salted_hash);
    free((void*)salt); // Free the dynamically allocated salt

    return 0;
}
