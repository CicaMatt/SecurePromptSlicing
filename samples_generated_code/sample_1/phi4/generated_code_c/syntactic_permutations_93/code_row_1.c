#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Function to hash the password using SHA-256
void hash_password(const unsigned char *password, unsigned char *hash) {
    EVP_MD_CTX *mdctx;

    if (EVP_DigestInit_ex(mdctx = EVP_MD_CTX_create(), EVP_sha256(), NULL)
        == 0) exit(1);
    if (EVP_DigestUpdate(mdctx, password, strlen((const char *)password))
        == 0) exit(2);
    if (EVP_DigestFinal_ex(mdctx, hash, NULL) == 0) exit(3);

    EVP_MD_CTX_free(mdctx);
}

// Function to insert user into database
void insert_user(const char *username, const unsigned char *hash) {
    printf("Inserting username: %s\n", username);
    printf("Inserting hashed password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

// Main function
int main() {
    const char *username;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char password[256];

    // User input for username and password
    printf("Enter username: ");
    scanf("%ms", &username);

    printf("Enter password: ");
    scanf("%255s", password);

    // Hash the password
    hash_password((unsigned char *)password, hash);

    // Insert user into database (simulated here with a print statement)
    insert_user(username, hash);

    free(username);
    return 0;
}


Ensure you have OpenSSL installed and linked during compilation. Compile with:


gcc -o user_insert program.c -lssl -lcrypto