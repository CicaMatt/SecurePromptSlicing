#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(char *salt) {
    FILE *f = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, f);
    fclose(f);
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    unsigned char combined[MAX_PASSWORD + SALT_SIZE];
    strncpy((char *)combined, password, MAX_PASSWORD);
    strncat((char *)combined, salt, SALT_SIZE);
    SHA256(combined, MAX_PASSWORD + SALT_SIZE, hash);
}

int insert_into_database(const char *username, const unsigned char *hash) {
    printf("INSERT INTO users (username, password_hash) VALUES ('%s', '", username);
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x", hash[i]);
    }
    printf("');\n");
    return 1; // Simulate success
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    if (insert_into_database(username, hash)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}