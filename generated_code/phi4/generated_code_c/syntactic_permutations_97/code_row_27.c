#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Mock function to simulate database query
int check_user_exists(const char *username) {
    // Simulate checking in a database
    return 0; // Return 1 if exists, 0 otherwise
}

// Mock function to simulate inserting into a database
void insert_user(const char *username, const unsigned char *hashed_password) {
    printf("Inserting user %s with hashed password.\n", username);
}

// Function to hash the password using SHA-256
unsigned char* hash_password(const char *password) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;

    // Create and initialize context
    if(!(mdctx = EVP_MD_CTX_create())) exit(1);

    // Initialize the digest operation with SHA-256
    if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) exit(1);

    // Provide password to be hashed
    if(1 != EVP_DigestUpdate(mdctx, password, strlen(password))) exit(1);

    // Finalize the hash
    unsigned char *md_value;
    md_value = malloc(EVP_MAX_MD_SIZE);
    if(!md_value) exit(1);

    if(1 != EVP_DigestFinal_ex(mdctx, md_value, &md_len)) exit(1);
    
    EVP_MD_CTX_destroy(mdctx);

    // Return the hashed password
    return md_value;
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];
    unsigned char *hashed_password;

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    if (check_user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    hashed_password = hash_password(password);

    printf("Enter first name: ");
    fgets(first_name, sizeof(first_name), stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter last name: ");
    fgets(last_name, sizeof(last_name), stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    insert_user(username, hashed_password);

    printf("Registration succeeded.\n");

    free(hashed_password);
    return 0;
}