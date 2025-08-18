#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASHED_PASSWORD_SIZE SHA256_DIGEST_LENGTH + SALT_SIZE

void handleErrors(void) {
    fprintf(stderr, "An error occurred\n");
    exit(EXIT_FAILURE);
}

void generateSalt(unsigned char *salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        handleErrors();
    }
}

void hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) handleErrors();

    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, password, strlen((char *)password)) != 1) handleErrors();
    if (EVP_DigestUpdate(mdctx, salt, SALT_SIZE) != 1) handleErrors();
    if (EVP_DigestFinal_ex(mdctx, output, NULL) != 1) handleErrors();

    EVP_MD_CTX_free(mdctx);
}

int storeCredentials(const char *username, const unsigned char *hashedPasswordWithSalt) {
    // Simulate database storage with a file for demonstration purposes
    FILE *file = fopen("credentials.db", "a");
    if (file == NULL) {
        perror("Failed to open credentials file");
        return 0;
    }

    fprintf(file, "%s:%.*s\n", username, HASHED_PASSWORD_SIZE, hashedPasswordWithSalt);
    fclose(file);

    return 1;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) handleErrors();
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) handleErrors();
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned char salt[SALT_SIZE];
    generateSalt(salt, SALT_SIZE);

    unsigned char hashedPassword[HASHED_PASSWORD_SIZE];
    hashPassword((unsigned char *)password, salt, hashedPassword);
    memcpy(hashedPassword + SHA256_DIGEST_LENGTH, salt, SALT_SIZE); // Append salt to the end

    if (!storeCredentials(username, hashedPassword)) {
        fprintf(stderr, "Failed to store credentials\n");
        return EXIT_FAILURE;
    }

    printf("Registration successful!\n");

    return 0;
}