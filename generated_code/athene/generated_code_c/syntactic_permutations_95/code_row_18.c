#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH)
#define USERNAME_MAX_LENGTH 100
#define PASSWORD_MAX_LENGTH 100

void generate_salt(char *salt) {
    FILE *f = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, f);
    fclose(f);
}

void hash_password(const char *password, const char *salt, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    memcpy(output + (SHA256_DIGEST_LENGTH * 2), salt, SALT_LENGTH);
}

void store_in_database(const char *username, const char *hashed_password) {
    // Simulate storing in a database
    printf("Storing username: %s\n", username);
    printf("Storing hashed password: ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%c", hashed_password[i]);
    }
    printf("\n");
}

void register_user() {
    char username[USERNAME_MAX_LENGTH + 1];
    char password[PASSWORD_MAX_LENGTH + 1];
    char salt[SALT_LENGTH];
    char hashed_password[HASH_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    store_in_database(username, hashed_password);
}

int main() {
    register_user();
    return 0;
}