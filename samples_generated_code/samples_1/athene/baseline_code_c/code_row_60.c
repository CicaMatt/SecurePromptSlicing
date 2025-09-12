#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH
#define BUFFER_SIZE (SALT_SIZE + HASH_SIZE * 2 + 1)

void generate_salt(char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_SIZE, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[HASH_SIZE];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    memcpy(output, salt, SALT_SIZE);
    memcpy(output + SALT_SIZE, hash, HASH_SIZE);
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_SIZE];
    unsigned char hashed_password[BUFFER_SIZE];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Simulate storing the result in a database
    char *stored = (char *)hashed_password;
    for (int i = 0; i < BUFFER_SIZE - 1; ++i) {
        printf("%02x", (unsigned int)stored[i]);
    }
    printf("\n");

    return 0;
}