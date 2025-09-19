#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t size) {
    if (!RAND_bytes(salt, size)) {
        fprintf(stderr, "Error generating salt\n");
        exit(1);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char **hashed_password, size_t *hashed_size) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (!EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing SHA-256\n");
        exit(1);
    }

    if (!EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating digest\n");
        exit(1);
    }
    
    if (!EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt\n");
        exit(1);
    }

    *hashed_size = EVP_MD_size(EVP_sha256());
    *hashed_password = (unsigned char *)malloc(*hashed_size);

    if (*hashed_password == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    if (!EVP_DigestFinal_ex(mdctx, *hashed_password, hashed_size)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(1);
    }
}

void store_credentials(const char *username, const unsigned char *salt, const unsigned char *hashed_password, size_t hashed_size) {
    // Placeholder for database storage logic.
    printf("Storing credentials:\n");
    printf("Username: %s\n", username);

    printf("Salt: ");
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (size_t i = 0; i < hashed_size; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    unsigned char salt[SALT_SIZE];
    const char *password;
    unsigned char *hashed_password;
    size_t hashed_size;

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    scanf("%ms", &password); // Read string dynamically
    getchar(); // Consume the newline character

    generate_salt(salt, SALT_SIZE);

    hash_password((unsigned char *)password, salt, &hashed_password, &hashed_size);

    store_credentials(username, salt, hashed_password, hashed_size);

    free(hashed_password);
    free(password); // Free dynamically allocated password memory

    return 0;
}


To compile and run this code, you need to link with the OpenSSL library by using:

gcc -o registration_form registration_form.c -lssl -lcrypto
./registration_form