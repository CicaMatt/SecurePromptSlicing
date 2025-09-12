#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define SALT_SIZE 8

void generate_salt(unsigned char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, sizeof(unsigned char), SALT_SIZE, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hash(const unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    print_hash(hash);

    return 0;
}