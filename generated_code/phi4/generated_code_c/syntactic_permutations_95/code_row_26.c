#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16

void handleErrors(void) {
    fprintf(stderr, "Error\n");
    exit(EXIT_FAILURE);
}

int generate_salt(unsigned char *salt, size_t length) {
    if (!RAND_bytes(salt, length)) {
        handleErrors();
    }
    return 1;
}

int hash_password(const char *password, const unsigned char *salt, unsigned char **hash_output) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) handleErrors();
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) handleErrors();
    if (1 != EVP_DigestFinal_ex(mdctx, *hash_output, &md_len)) handleErrors();

    EVP_MD_CTX_free(mdctx);
    return 1;
}

int store_user(const char *username, unsigned char *salt, unsigned char *hashed_password) {
    FILE *file = fopen("users.db", "a");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s ", username);

    for (int i = 0; i < SALT_LENGTH + EVP_MAX_MD_SIZE; ++i) {
        fprintf(file, "%02x", hashed_password[i]);
    }
    fputc('\n', file);

    fclose(file);
    return 1;
}

void register_user() {
    char username[64];
    char password[64];
    unsigned char salt[SALT_LENGTH];
    unsigned char *hashed_password;
    
    printf("Enter username: ");
    scanf("%63s", username);

    printf("Enter password: ");
    scanf("%63s", password);

    if (!generate_salt(salt, SALT_LENGTH)) handleErrors();

    hashed_password = (unsigned char *)malloc(EVP_MAX_MD_SIZE);
    if (!hashed_password) handleErrors();

    if (!hash_password(password, salt, &hashed_password)) handleErrors();
    
    unsigned char *combined_hashed_password = malloc(SALT_LENGTH + EVP_MAX_MD_SIZE);
    memcpy(combined_hashed_password, salt, SALT_LENGTH);
    memcpy(combined_hashed_password + SALT_LENGTH, hashed_password, EVP_MAX_MD_SIZE);

    if (!store_user(username, salt, combined_hashed_password)) handleErrors();

    free(hashed_password);
    free(combined_hashed_password);

    printf("User registered successfully.\n");
}

int main() {
    register_user();
    return 0;
}


**Dependencies:**  
This code requires OpenSSL to compile and run. To install it on a Unix-like system, use your package manager (e.g., `apt-get install libssl-dev` on Debian-based systems).

To compile the program:

gcc -o registration_program registration_program.c -lssl -lcrypto


Then you can run the executable with:

./registration_program