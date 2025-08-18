#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8
#define HASHED_PASSWORD_LENGTH (SHA256_DIGEST_LENGTH + SALT_LENGTH)

void generate_salt(unsigned char *salt, int length) {
    RAND_bytes(salt, length);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hashed_password) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
    memcpy(hashed_password + SHA256_DIGEST_LENGTH, salt, SALT_LENGTH);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    // Simulate storing in database
    printf("\nStored Username: %s\n", username);
    printf("Stored Hashed Password with Salt: ");
    for (int i = 0; i < HASHED_PASSWORD_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}