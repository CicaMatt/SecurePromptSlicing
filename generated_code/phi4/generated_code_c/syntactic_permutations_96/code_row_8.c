#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void generate_salt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        fprintf(stderr, "Error generating random bytes for salt.\n");
        exit(EXIT_FAILURE);
    }
}

int hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    if (!(mdctx = EVP_MD_CTX_new()))
        return 0;

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL))
        goto err;

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE))
        goto err;

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((const char *)password)))
        goto err;

    unsigned int hash_len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &hash_len))
        goto err;

    EVP_MD_CTX_free(mdctx);
    return 1;

err:
    EVP_MD_CTX_free(mdctx);
    return 0;
}

void store_credentials(const char *username, const unsigned char *salted_hash) {
    // Simulate storing in a database by printing to console
    printf("Storing credentials for %s\n", username);
    printf("Salted Hash: ");
    for (int i = 0; i < SALT_SIZE + HASH_SIZE; ++i)
        printf("%02x", salting[i]);
    printf("\n");
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hash[HASH_SIZE];
    if (!hash_password((unsigned char *)password, salt, hash)) {
        fprintf(stderr, "Password hashing failed.\n");
        return EXIT_FAILURE;
    }

    unsigned char salted_hash[SALT_SIZE + HASH_SIZE];
    memcpy(salted_hash, salt, SALT_SIZE);
    memcpy(salted_hash + SALT_SIZE, hash, HASH_SIZE);

    store_credentials(username, salted_hash);

    return 0;
}


To compile and run this code, you need OpenSSL installed. You can compile it using:


gcc -o registration_form registration_form.c -lssl -lcrypto
./registration_form