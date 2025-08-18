#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *output_buffer) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output_buffer + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    char username[100];
    char password[100];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter your password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);
    printf("Hashed Password: %s\n", hashed_password);

    return 0;
}