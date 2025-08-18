#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_LENGTH 256

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

unsigned char *hashPassword(const unsigned char *password, size_t length, unsigned char **md) {
    const EVP_MD *md_type = EVP_sha256();

    if (EVP_DigestInit_ex(*md, md_type, NULL) != 1)
        handleErrors();

    if (EVP_DigestUpdate(*md, password, length) != 1)
        handleErrors();

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    if (EVP_DigestFinal_ex(*md, hash, &hash_len) != 1)
        handleErrors();

    *md = NULL;
    EVP_MD_CTX_free(*md);

    unsigned char *result = malloc(hash_len);
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memcpy(result, hash, hash_len);
    return result;
}

int main() {
    const char *username = NULL;
    const unsigned char *password = NULL;

    printf("Enter username: ");
    getline(&username, &MAX_LENGTH, stdin);

    printf("Enter password: ");
    getline(&password, &MAX_LENGTH, stdin);

    // Remove newline character from input
    size_t length = strlen(username);
    if (length > 0 && username[length - 1] == '\n') {
        username[--length] = '\0';
    }
    length = strlen((char *)password);
    if (length > 0 && password[length - 1] == '\n') {
        password[--length] = '\0';
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!mdctx) handleErrors();

    unsigned char *hashed_password = hashPassword(password, strlen((char *)password), &mdctx);

    printf("Hashed Password: ");
    for (size_t i = 0; i < EVP_sha256()->digest_size; ++i)
        printf("%02x", hashed_password[i]);
    printf("\n");

    // Here you would insert the username and hashed password into your database
    // For demonstration, we'll just print them

    printf("Inserting into database: Username = %s, Hashed Password = ", username);
    for (size_t i = 0; i < EVP_sha256()->digest_size; ++i)
        printf("%02x", hashed_password[i]);
    printf("\n");

    free(hashed_password);
    EVP_MD_CTX_free(mdctx);

    return 0;
}


To compile and run this code, you need to have OpenSSL installed on your system. You can compile the program using a command similar to:


gcc -o password_hasher password_hasher.c -lssl -lcrypto
./password_hasher


This code does not include actual database interaction for inserting the username and hashed password due to the wide variety of databases and their respective C libraries. You would need to use a specific library for your chosen database (e.g., MySQL, PostgreSQL) and write the appropriate SQL query to insert the data into the database.