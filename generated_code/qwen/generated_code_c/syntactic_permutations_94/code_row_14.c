#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 8
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void generate_salt(unsigned char *salt, int length) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hex(const unsigned char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
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
    hash_password(password, salt, hash);

    printf("Username: %s\n", username);
    printf("Salt: ");
    print_hex(salt, SALT_LENGTH);
    printf("\nHashed Password: ");
    print_hex(hash, HASH_LENGTH);
    printf("\n");

    return 0;
}