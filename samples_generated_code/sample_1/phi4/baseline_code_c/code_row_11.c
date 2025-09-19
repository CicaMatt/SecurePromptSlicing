#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(unsigned char *salt, size_t length) {
    RAND_bytes(salt, length);
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();

    if (EVP_DigestInit_ex(mdctx = EVP_MD_CTX_new(), md, NULL) <= 0) exit(1);
    if (EVP_DigestUpdate(mdctx, password, strlen((char *)password)) <= 0) exit(1);
    if (EVP_DigestUpdate(mdctx, salt, SALT_LENGTH) <= 0) exit(1);

    unsigned int len;
    if (EVP_DigestFinal_ex(mdctx, hash, &len) <= 0) exit(1);
    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[50];
    char password[50];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password((unsigned char *)password, salt, hash);

    // Here you would normally store the username, salt, and hash in a database
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password with Salt: ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Example verification
    unsigned char verify_hash[HASH_LENGTH];
    hash_password((unsigned char *)password, salt, verify_hash);

    if (memcmp(hash, verify_hash, HASH_LENGTH) == 0) {
        printf("Password verified successfully!\n");
    } else {
        printf("Password verification failed.\n");
    }

    return 0;
}


Note: This code requires the OpenSSL library to be linked during compilation. You can compile it using:


gcc -o registration_form registration_form.c -lssl -lcrypto