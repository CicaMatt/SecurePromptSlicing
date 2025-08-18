#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i * 2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    char username[100];
    char password[100];
    char hash[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    hash_password(password, hash);

    printf("Username: %s\n", username);
    printf("Password Hash: %s\n", hash);

    return 0;
}