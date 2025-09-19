#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void handleErrors(void) {
    fprintf(stderr, "An error occurred.\n");
    exit(EXIT_FAILURE);
}

unsigned char *generate_salt(size_t length) {
    unsigned char *salt = malloc(length);
    if (!salt) handleErrors();
    if (RAND_bytes(salt, length) != 1) handleErrors();
    return salt;
}

char *hash_password(const unsigned char *password, const unsigned char *salt, size_t password_len, size_t salt_len) {
    EVP_MD_CTX *mdctx;
    unsigned char hash[HASH_LENGTH];
    char *hashed_pass = malloc(HASH_LENGTH + salt_len + 1);
    if (!hashed_pass) handleErrors();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, password, password_len) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, salt, salt_len) != 1) handleErrors();
    if (EVP_DigestFinal_ex(mdctx, hash, NULL) != 1) handleErrors();

    EVP_MD_CTX_free(mdctx);

    for (int i = 0; i < HASH_LENGTH; ++i) {
        sprintf(hashed_pass + i * 2, "%02x", hash[i]);
    }

    memcpy(hashed_pass + HASH_LENGTH * 2, salt, salt_len);
    hashed_pass[HASH_LENGTH * 2 + salt_len] = '\0';

    return hashed_pass;
}

void store_credentials(const char *username, const unsigned char *hashed_password) {
    // Simulate storing in a database by writing to a file
    FILE *file = fopen("credentials.txt", "a");
    if (!file) handleErrors();
    fprintf(file, "%s:%.*s\n", username, HASH_LENGTH * 2 + SALT_LENGTH, hashed_password);
    fclose(file);
}

int main() {
    char username[100];
    unsigned char password[256];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    fgets((char *)password, sizeof(password), stdin);
    size_t password_len = strlen((char *)password) - 1; // Remove newline
    password[password_len] = '\0';

    unsigned char *salt = generate_salt(SALT_LENGTH);
    char *hashed_password = hash_password(password, salt, password_len, SALT_LENGTH);

    store_credentials(username, hashed_password);

    free(hashed_password);
    free(salt);

    printf("Registration successful!\n");
    
    return 0;
}