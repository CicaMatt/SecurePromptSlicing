#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>  // Ensure OpenSSL library is installed

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH
#define BUFFER_SIZE 64

void generate_salt(unsigned char *salt, size_t salt_size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_size, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash_output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Final(hash_output, &sha256);
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // Mock function to simulate storing in a database
    printf("Storing credentials for %s\n", username);
    for (int i = 0; i < HASH_SIZE + SALT_SIZE; i++) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    if (fgets(username, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash_output[HASH_SIZE];
    hash_password(password, salt, hash_output);

    size_t combined_size = HASH_SIZE + SALT_SIZE;
    unsigned char *salted_hash = malloc(combined_size);
    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, hash_output, HASH_SIZE);

    store_credentials(username, salted_hash);

    free(salted_hash);
    return 0;
}