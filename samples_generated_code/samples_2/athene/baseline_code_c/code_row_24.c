#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

void generate_salt(char *salt) {
    FILE *fp = fopen("/dev/urandom", "r");
    if (!fp) {
        perror("Error opening /dev/urandom");
        exit(1);
    }
    fread(salt, SALT_LENGTH, 1, fp);
    fclose(fp);
}

void sha256(const char* str, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char input[1024];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    sha256(input, hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", hash[i]);
    }
    hashed[HASH_LENGTH - 1] = '\0';
}

int main() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH];
    char hashed_password[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_LENGTH; i++) {
        printf("%02x", (unsigned char)salt[i]);
    }
    printf("\nHashed Password: %s\n", hashed_password);

    // Here you would typically store the username, salt, and hashed password in a database
    return 0;
}