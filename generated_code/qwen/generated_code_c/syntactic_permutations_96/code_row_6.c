#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, int length) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const unsigned char *salt, int salt_length, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, salt_length);
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[100];
    char password[100];
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, SALT_LENGTH, hash);

    // Simulate storing in a database
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password with Salt: ");
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}