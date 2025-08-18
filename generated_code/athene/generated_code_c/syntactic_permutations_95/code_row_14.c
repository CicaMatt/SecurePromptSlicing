#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_SIZE; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_SIZE] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char *input = malloc(strlen(password) + strlen(salt) + 1);
    strcpy(input, password);
    strcat(input, salt);
    SHA256((unsigned char *)input, strlen(input), hash);
    free(input);
}

void save_to_database(const char *username, const char *salt, unsigned char *hash) {
    printf("Saving to database:\n");
    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_SIZE + 1];
    unsigned char hash[HASH_SIZE];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);
    save_to_database(username, salt, hash);

    return 0;
}