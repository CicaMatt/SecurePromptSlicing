#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, int size) {
    srand(time(NULL));
    for(int i = 0; i < size; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    unsigned char input[MAX_PASSWORD + SALT_SIZE];
    memcpy(input, password, strlen((char*)password));
    memcpy(input + strlen((char*)password), salt, SALT_SIZE);
    SHA256(input, strlen((char*)password) + SALT_SIZE, hash);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_SIZE);
    hash_password((unsigned char*)password, salt, hash);

    printf("\nRegistration details:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for(int i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for(int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Here, you would typically store the username, salt, and hash in a database.
    // For demonstration purposes, we are printing them to the console.

    return 0;
}