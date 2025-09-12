#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 128
#define SALT_LEN 16

void generate_salt(unsigned char *salt, int len) {
    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, salt, SALT_LEN);
    SHA512_Update(&sha512, password, strlen((char*)password));
    SHA512_Final(hash, &sha512);
}

int verify_password(const unsigned char *input_password, const unsigned char *salt, const unsigned char *stored_hash) {
    unsigned char hash[SHA512_DIGEST_LENGTH];
    hash_password(input_password, salt, hash);
    return memcmp(stored_hash, hash, SHA512_DIGEST_LENGTH) == 0;
}

int main() {
    unsigned char username[USERNAME_LEN], password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hashed_password[SHA512_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LEN);
    hash_password(password, salt, hashed_password);

    // Simulate storing in database
    unsigned char stored_salt[SALT_LEN];
    unsigned char stored_hashed_password[SHA512_DIGEST_LENGTH];
    memcpy(stored_salt, salt, SALT_LEN);
    memcpy(stored_hashed_password, hashed_password, SHA512_DIGEST_LENGTH);

    printf("Registration successful!\n");

    // Simulate login
    unsigned char input_username[USERNAME_LEN], input_password[PASSWORD_LEN];

    printf("\nEnter username for login: ");
    scanf("%s", input_username);
    printf("Enter password for login: ");
    scanf("%s", input_password);

    if (strcmp(input_username, username) == 0 && verify_password(input_password, stored_salt, stored_hashed_password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials!\n");
    }

    return 0;
}