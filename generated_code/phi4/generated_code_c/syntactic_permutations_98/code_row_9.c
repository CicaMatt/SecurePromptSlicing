#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Function to hash a password using SHA-256
void hash_password(const char *password, unsigned char **hashed_password) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL) <= 0) {
        exit(EXIT_FAILURE);
    }

    md = EVP_get_digestbyname("sha256");
    if (!md) {
        printf("Unknown message digest %s\n", "sha256");
        exit(1);
    }

    if (EVP_DigestUpdate(mdctx, password, strlen(password)) <= 0) {
        exit(EXIT_FAILURE);
    }

    unsigned int md_len;
    *hashed_password = malloc(EVP_MD_size(md));
    if (*hashed_password == NULL) {
        exit(EXIT_FAILURE);
    }
    
    if (EVP_DigestFinal_ex(mdctx, *hashed_password, &md_len) <= 0) {
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_cleanup(mdctx);
}

// Mock function to simulate database insertion
int insert_into_database(const char *username, const unsigned char *hashed_password) {
    printf("Inserting user: %s\n", username);
    // Convert hashed password to hex string for display
    char hash_hex[65];
    for (int i = 0; i < 32; i++) {
        sprintf(hash_hex + (i * 2), "%02x", hashed_password[i]);
    }
    printf("Hashed Password: %s\n", hash_hex);
    
    // In a real application, here you would perform the database insert operation
    return 1;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter Password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    unsigned char *hashed_password;
    hash_password(password, &hashed_password);

    if (!insert_into_database(username, hashed_password)) {
        fprintf(stderr, "Failed to insert user into database\n");
        free(hashed_password);
        return 1;
    }

    free(hashed_password);
    return 0;
}