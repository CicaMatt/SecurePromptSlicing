#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void generate_salt(char *salt, size_t len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (fp == NULL) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, len - 1, fp);
    fclose(fp);
    salt[len - 1] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    memcpy(output, hash, SHA256_DIGEST_LENGTH);
}

int main() {
    char username[100];
    char password[100];
    char salt[32]; // 32 bytes for salt
    unsigned char hashed_password[SHA256_DIGEST_LENGTH + 32 + 1]; // Hash + Salt + Null terminator

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, sizeof(salt));
    hash_password(password, salt, hashed_password);

    // Concatenate salt and hashed password
    memcpy(hashed_password + SHA256_DIGEST_LENGTH, salt, 32);
    hashed_password[SHA256_DIGEST_LENGTH + 32] = '\0';

    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH + 32; i++) {
        printf("%02x", (unsigned int)hashed_password[i]);
    }
    printf("\n");

    // In a real application, you would store the username and hashed_password in a database.
    return 0;
}