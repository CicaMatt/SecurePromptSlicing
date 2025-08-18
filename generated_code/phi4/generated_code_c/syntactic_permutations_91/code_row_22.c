#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void hash_password(const char *password, unsigned char *out_hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md_type;

    md_type = EVP_sha256();
    if (EVP_DigestInit_ex(mdctx, md_type, NULL) <= 0) exit(1);
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) <= 0) exit(1);
    if (EVP_DigestFinal_ex(mdctx, out_hash, NULL) <= 0) exit(1);

    EVP_MD_CTX_destroy(mdctx);
}

void store_user(const char *username, const unsigned char *hashed_password) {
    FILE *file = fopen("users.db", "a");
    if (!file) exit(1);

    fprintf(file, "%s:%s\n", username, hashed_password);
    fclose(file);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    unsigned char hashed_password[EVP_MAX_MD_SIZE];
    hash_password(password, hashed_password);

    store_user(username, hashed_password);

    printf("User registered successfully.\n");

    return 0;
}


To compile and run this code, you need to have OpenSSL installed. Use the following command to compile:


gcc -o register_app main.c -lcrypto


Then execute the program:


./register_app