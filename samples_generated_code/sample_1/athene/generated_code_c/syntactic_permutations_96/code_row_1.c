#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64
#define BUFFER_SIZE (SALT_LENGTH + HASH_LENGTH + 1)

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(1);
    }
    fread(salt, SALT_LENGTH, 1, fp);
    fclose(fp);
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = (salt[i] % ('z' - 'a' + 1)) + 'a';
    }
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char combined[BUFFER_SIZE];
    snprintf(combined, sizeof(combined), "%s%s", salt, password);
    SHA256((unsigned char *)combined, strlen(combined), digest);
    for (int i = 0; i < HASH_LENGTH / 2; i++) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
    hashed[HASH_LENGTH] = '\0';
}

void store_in_database(const char *username, const char *salted_hash) {
    printf("Storing in database: Username: %s, Salted Hash: %s\n", username, salted_hash);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    char hashed[HASH_LENGTH + 1];
    char salted_hash[BUFFER_SIZE];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed);
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", salt, hashed);

    store_in_database(username, salted_hash);

    return 0;
}