#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 8
#define HASH_LEN SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t salt_len) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Failed to open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, salt_len, fp);
    fclose(fp);
}

void hash_password(const char *password, const char *salt, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, hash);

    printf("Salt: ");
    for (int i = 0; i < SALT_LEN; i++) {
        printf("%02x", (unsigned char)salt[i]);
    }
    printf("\n");

    printf("Hashed Password: ");
    for (int i = 0; i < HASH_LEN; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}