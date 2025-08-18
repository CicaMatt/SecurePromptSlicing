#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT_LENGTH 16

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

char* generateSalt() {
    unsigned char salt[SALT_LENGTH];
    if (!RAND_bytes(salt, sizeof(salt))) {
        handleErrors();
    }
    char *saltStr = (char *)malloc(SALT_LENGTH + 1);
    for (int i = 0; i < SALT_LENGTH; i++) {
        sprintf(&saltStr[i*2], "%02x", salt[i]);
    }
    saltStr[SALT_LENGTH * 2] = '\0';
    return saltStr;
}

char* hashPassword(const char *password, const char *salt) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;
    unsigned char md[EVP_MAX_MD_SIZE];

    if (!(mdctx = EVP_MD_CTX_new())) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH * 2)) handleErrors(); // Salt is hex string
    if (1 != EVP_DigestFinal_ex(mdctx, md, &md_len)) handleErrors();

    EVP_MD_CTX_free(mdctx);

    char *digest = (char *)malloc(EVP_MAX_MD_SIZE * 2 + 1);
    for (unsigned int i = 0; i < md_len; ++i) {
        sprintf(&digest[i*2], "%02x", md[i]);
    }
    digest[md_len * 2] = '\0';
    
    return digest;
}

void storeCredentials(const char *username, const char *saltedHash) {
    // Simulate storing in a database
    FILE *file = fopen("credentials.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s:%s\n", username, saltedHash);
    fclose(file);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    char *salt = generateSalt();
    char *hashedPassword = hashPassword(password, salt);
    char *saltedHash = (char *)malloc(strlen(salt) + strlen(hashedPassword) + 1);
    strcpy(saltedHash, salt);
    strcat(saltedHash, hashedPassword);

    storeCredentials(username, saltedHash);

    printf("Registration successful!\n");

    free(salt);
    free(hashedPassword);
    free(saltedHash);

    return 0;
}