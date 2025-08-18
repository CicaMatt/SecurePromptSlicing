#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 100
#define SALT_LENGTH 16

void generateSalt(unsigned char *salt, int length) {
    FILE* urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, urandom);
    fclose(urandom);
}

void hashPassword(const char *password, const unsigned char *salt, int saltLength, unsigned char *hash) {
    unsigned char saltedPassword[PASSWORD_LENGTH + SALT_LENGTH];
    memcpy(saltedPassword, salt, saltLength);
    strcpy((char*)salTEDPassword + saltLength, password);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, saltedPassword, strlen(password) + saltLength);
    SHA256_Final(hash, &sha256);
}

void storeInDatabase(const char *username, const unsigned char *salt, unsigned char *hash) {
    printf("Storing in database:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    generateSalt(salt, SALT_LENGTH);
    hashPassword(password, salt, SALT_LENGTH, hash);
    storeInDatabase(username, salt, hash);

    return 0;
}