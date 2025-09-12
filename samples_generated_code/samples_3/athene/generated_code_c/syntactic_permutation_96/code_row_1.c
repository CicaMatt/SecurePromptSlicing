#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, SALT_SIZE, 1, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[HASH_SIZE + SALT_SIZE + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

void store_to_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s and salted hash: %s to database\n", username, salted_hash);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE + 1];
    char hashed_password[HASH_SIZE * 2 + 1];
    char salted_hash[HASH_SIZE * 2 + SALT_SIZE + 2];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    salt[SALT_SIZE] = '\0';

    hash_password(password, salt, hashed_password);
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", salt, hashed_password);

    store_to_database(username, salted_hash);

    return 0;
}