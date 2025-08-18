#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH
#define MAX_USERNAME 32
#define MAX_PASSWORD 32

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[HASH_SIZE];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    memcpy(output, salt, SALT_SIZE);
    memcpy(output + SALT_SIZE, hash, HASH_SIZE);
}

void store_in_database(const char *username, const unsigned char *salted_hash) {
    printf("Storing username: %s\n", username);
    for (int i = 0; i < SALT_SIZE + HASH_SIZE; ++i) {
        printf("%02x", salted_hash[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_SIZE];
    unsigned char salted_hash[SALT_SIZE + HASH_SIZE];

    printf("Enter username: ");
    scanf("%31s", username);

    printf("Enter password: ");
    scanf("%31s", password);

    generate_salt(salt);
    hash_password(password, salt, salted_hash);
    store_in_database(username, salted_hash);

    return 0;
}