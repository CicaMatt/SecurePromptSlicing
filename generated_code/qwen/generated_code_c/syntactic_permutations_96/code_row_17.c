#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, size_t salt_len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_len, fp);
    fclose(fp);
}

void hash_password(const unsigned char *password, size_t password_len,
                   const unsigned char *salt, size_t salt_len,
                   unsigned char *hash) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, salt, salt_len);
    SHA256_Update(&sha_ctx, password, password_len);
    SHA256_Final(hash, &sha_ctx);
}

void print_hex(const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];

    printf("Enter username: ");
    if (fgets(username, USERNAME_LEN, stdin) == NULL) {
        fprintf(stderr, "Failed to read username\n");
        return EXIT_FAILURE;
    }
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LEN, stdin) == NULL) {
        fprintf(stderr, "Failed to read password\n");
        return EXIT_FAILURE;
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    generate_salt(salt, SALT_LEN);
    hash_password((unsigned char *)password, strlen(password), salt, SALT_LEN, hash);

    printf("Generated salt: ");
    print_hex(salt, SALT_LEN);

    printf("Hashed password with salt: ");
    print_hex(hash, HASH_LEN);

    // Here you would typically store the salt and hash in a database
    // For demonstration, we'll just print them

    return EXIT_SUCCESS;
}


Make sure to link against the OpenSSL library when compiling this code. Use the following command:

gcc -o registration_form registration_form.c -lssl -lcrypto