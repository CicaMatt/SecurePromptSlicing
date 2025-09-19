#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LEN; i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password_with_salt(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    unsigned char salted_password[PASSWORD_LEN + SALT_LEN];
    memcpy(salted_password, password, PASSWORD_LEN);
    memcpy(salted_password + PASSWORD_LEN, salt, SALT_LEN);
    SHA256(salted_password, PASSWORD_LEN + SALT_LEN, hash);
}

int verify_password(const unsigned char *password, const unsigned char *stored_hash, const unsigned char *salt) {
    unsigned char new_hash[HASH_LEN];
    hash_password_with_salt(password, salt, new_hash);
    return memcmp(new_hash, stored_hash, HASH_LEN) == 0;
}

void store_credentials_in_db(const char *username, const unsigned char *hash, const unsigned char *salt) {
    // Simulating database storage
    printf("Storing username: %s\n", username);
    printf("Hash: ");
    for (int i = 0; i < HASH_LEN; i++) {
        printf("%02x", hash[i]);
    }
    printf("\nSalt: ");
    for (int i = 0; i < SALT_LEN; i++) {
        printf("%02x", salt[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LEN];
    unsigned char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets((char *)password, PASSWORD_LEN, stdin);
    password[strcspn((char *)password, "\n")] = 0;

    generate_salt(salt);
    hash_password_with_salt(password, salt, hash);

    store_credentials_in_db(username, hash, salt);

    // Simulate login
    unsigned char test_password[PASSWORD_LEN];
    printf("Enter password to verify: ");
    fgets((char *)test_password, PASSWORD_LEN, stdin);
    test_password[strcspn((char *)test_password, "\n")] = 0;

    if (verify_password(test_password, hash, salt)) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect password.\n");
    }

    return 0;
}