#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, size, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_to_database(const char *username, const unsigned char *salt_and_hash) {
    printf("Storing username: %s\n", username);
    for (int i = 0; i < SALT_SIZE + HASH_SIZE; i++) {
        printf("%02x", salt_and_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];
    unsigned char salt_and_hash[SALT_SIZE + HASH_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password(password, salt, hash);

    memcpy(salt_and_hash, salt, SALT_SIZE);
    memcpy(salt_and_hash + SALT_SIZE, hash, HASH_SIZE);

    store_to_database(username, salt_and_hash);

    return 0;
}