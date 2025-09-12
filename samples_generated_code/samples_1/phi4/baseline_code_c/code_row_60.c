#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Function to generate a random salt
void generate_salt(unsigned char *salt, size_t length) {
    FILE *urandom = fopen("/dev/urandom", "rb");
    if (urandom != NULL) {
        fread(salt, 1, length, urandom);
        fclose(urandom);
    }
}

// Function to hash the password with a given salt
void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *output, size_t output_size) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) exit(EXIT_FAILURE);

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(mdctx, salt, 16)) exit(EXIT_FAILURE); // Assuming a 16-byte salt
    if (1 != EVP_DigestFinal_ex(mdctx, output, NULL)) exit(EXIT_FAILURE);

    EVP_MD_CTX_free(mdctx);
}

int main() {
    char username[50];
    char password[50];

    unsigned char salt[16];
    unsigned char hashed_password[EVP_MAX_MD_SIZE];

    // Generate a random salt
    generate_salt(salt, sizeof(salt));

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    // Hash the password with the generated salt
    hash_password((unsigned char *)password, salt, hashed_password, sizeof(hashed_password));

    // Store the username, salt, and hashed password in a database (pseudo code)
    printf("Storing User:\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < sizeof(salt); i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (size_t i = 0; i < EVP_MD_size(EVP_sha256()); i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Here you would actually store the username, salt, and hashed password in your database

    return 0;
}