#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, size, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Final(output, &sha256);
}

void store_credentials(const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    // Simulate storing in a database
    printf("Storing credentials for user: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

void register_user() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, hashed_password);

    store_credentials(username, salt, hashed_password);
}

int main() {
    register_user();
    return 0;
}