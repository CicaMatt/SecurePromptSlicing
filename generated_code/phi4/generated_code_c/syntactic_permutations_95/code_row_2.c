#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, size_t size) {
    srand(time(NULL));
    for (size_t i = 0; i < size; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *output_hash, size_t output_size) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen((char *)password));
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Final(output_hash, &sha256);

    // Truncate hash if needed
    if (output_size < HASH_SIZE) {
        memcpy(output_hash, output_hash + (HASH_SIZE - output_size), output_size);
    }
}

int main() {
    unsigned char username[256], password[256];
    unsigned char salt[SALT_SIZE], hashed_password[HASH_SIZE];
    
    printf("Enter Username: ");
    scanf("%255s", username);

    printf("Enter Password: ");
    scanf("%255s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char *)password, salt, hashed_password, HASH_SIZE);

    // Here you would store username, salt, and hashed_password to a database
    // For this example, we'll just print them

    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}