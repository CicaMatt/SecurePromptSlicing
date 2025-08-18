#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Function to hash password
void hash_password(const char* password, unsigned char** hashed_password, size_t* length) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;

    *hashed_password = (unsigned char*)malloc(EVP_MAX_MD_SIZE);
    if (!(*hashed_password)) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestFinal_ex(mdctx, *hashed_password, length);

    EVP_MD_CTX_free(mdctx);
}

// Function to store username and hashed password
void store_credentials(const char* username, const unsigned char* hashed_password, size_t length) {
    // For demonstration, we'll just print the values instead of storing in a database.
    printf("Storing credentials:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (size_t i = 0; i < length; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Here you would normally connect to a database and store the credentials
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char* hashed_password;
    size_t length;

    hash_password(password, &hashed_password, &length);

    store_credentials(username, hashed_password, length);

    free(hashed_password);

    return 0;
}