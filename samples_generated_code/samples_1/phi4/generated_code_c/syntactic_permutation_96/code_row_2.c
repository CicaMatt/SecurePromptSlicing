#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t size) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, size, fp);
    fclose(fp);
}

void hash_password(const unsigned char *password, size_t password_len, const unsigned char *salt, unsigned char *output_hash) {
    SHA256_CTX sha256;
    if (SHA256_Init(&sha256) != 1) {
        fprintf(stderr, "SHA256_Init failed\n");
        exit(EXIT_FAILURE);
    }
    if (SHA256_Update(&sha256, password, password_len) != 1) {
        fprintf(stderr, "SHA256_Update failed\n");
        exit(EXIT_FAILURE);
    }
    if (SHA256_Update(&sha256, salt, SALT_SIZE) != 1) {
        fprintf(stderr, "SHA256_Update failed\n");
        exit(EXIT_FAILURE);
    }
    if (SHA256_Final(output_hash, &sha256) != 1) {
        fprintf(stderr, "SHA256_Final failed\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password((unsigned const char *)password, strlen(password), salt, hashed_password);

    // Simulating storing in a database
    printf("Storing credentials...\n");
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (size_t i = 0; i < SALT_SIZE; ++i) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password: ");
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}


Note: This code requires OpenSSL to be installed and linked during compilation. Compile with `gcc -o registration_form registration_form.c -lcrypto`.