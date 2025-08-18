#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16

void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const unsigned char *password, const unsigned char *salt, size_t salt_length, unsigned char **hashed_output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    SHA256_Update(&sha256, password, strlen((const char *)password));
    SHA256_Update(&sha256, salt, salt_length);
    
    *hashed_output = (unsigned char*)malloc(SHA256_DIGEST_LENGTH + salt_length);
    memcpy(*hashed_output, salt, salt_length);
    SHA256_Final((*hashed_output) + salt_length, &sha256);
}

void store_credentials(const unsigned char *username, const unsigned char *password_hash, size_t password_hash_length) {
    FILE *file = fopen("credentials.txt", "ab");
    if (!file) {
        perror("Failed to open credentials file");
        exit(EXIT_FAILURE);
    }
    
    fwrite(username, 1, strlen((const char *)username), file);
    fwrite("\0", 1, 1, file); // Null character separator
    fwrite(password_hash, 1, password_hash_length, file);
    fwrite("\n", 1, 1, file); // Newline to separate entries

    fclose(file);
}

int main() {
    unsigned char salt[SALT_SIZE];
    generate_salt(salt, SALT_SIZE);

    char username[256];
    printf("Enter username: ");
    scanf("%255s", username);

    char password[256];
    printf("Enter password: ");
    scanf("%255s", password);

    unsigned char *hashed_password = NULL;
    hash_password((unsigned char*)password, salt, SALT_SIZE, &hashed_password);

    store_credentials((unsigned char*)username, hashed_password, SHA256_DIGEST_LENGTH + SALT_SIZE);

    free(hashed_password);
    return 0;
}