#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_SIZE 32

void handleErrors(void) {
    fprintf(stderr, "An error occurred.\n");
    exit(EXIT_FAILURE);
}

int generateSalt(unsigned char *salt) {
    return RAND_bytes(salt, SALT_LENGTH);
}

int hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    if (EVP_DigestInit_ex(mdctx = EVP_MD_CTX_new(), EVP_sha256(), NULL) != 1)
        handleErrors();

    if (EVP_DigestUpdate(mdctx, password, strlen((char *)password)) != 1 || 
        EVP_DigestUpdate(mdctx, salt, SALT_LENGTH) != 1 ||
        EVP_DigestFinal_ex(mdctx, hash, NULL) != 1) {
        handleErrors();
    }

    EVP_MD_CTX_free(mdctx);
    return 0;
}

void storeCredentials(const char *username, const unsigned char *hashedPassword, const unsigned char *salt) {
    // Simulating storing in a database
    printf("Storing credentials for user: %s\n", username);
    printf("Hashed Password with Salt: ");
    for (int i = 0; i < HASH_SIZE + SALT_LENGTH; ++i)
        printf("%02x", hashedPassword[i]);
    printf("\n");
}

void registerUser() {
    char username[100];
    char password[100];

    unsigned char salt[SALT_LENGTH];
    if (generateSalt(salt) != 1)
        handleErrors();

    unsigned char hash[HASH_SIZE];
    if (hashPassword((unsigned char *)password, salt, hash) != 0)
        handleErrors();

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hashedPasswordWithSalt[HASH_SIZE + SALT_LENGTH];
    memcpy(hashedPasswordWithSalt, hash, HASH_SIZE);
    memcpy(hashedPasswordWithSalt + HASH_SIZE, salt, SALT_LENGTH);

    storeCredentials(username, hashedPasswordWithSalt, salt);
}

int main(void) {
    registerUser();
    return 0;
}
