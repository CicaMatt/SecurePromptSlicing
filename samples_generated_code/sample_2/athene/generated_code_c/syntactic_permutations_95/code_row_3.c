#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    char combined[MAX_PASSWORD + SALT_LENGTH + 1];
    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    SHA256((const unsigned char *)combined, strlen(combined), hash);
}

void store_to_database(const char *username, const char *salted_hash) {
    printf("Storing username: %s, hashed password with salt: %s\n", username, salted_hash);
    // In a real application, this function would interact with an actual database
}

int main() {
    srand(time(NULL));

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salted_hash[2 * SHA256_DIGEST_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt);
    hash_password(password, salt, hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&salted_hash[i * 2], "%02x", (unsigned int)hash[i]);
    }
    strcat(salted_hash, salt);

    store_to_database(username, salted_hash);

    return 0;
}