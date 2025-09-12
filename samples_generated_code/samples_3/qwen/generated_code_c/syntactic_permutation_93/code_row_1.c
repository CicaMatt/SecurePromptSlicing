#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

void print_digest(unsigned char *digest) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    print_digest(hashed_password);

    return 0;
}