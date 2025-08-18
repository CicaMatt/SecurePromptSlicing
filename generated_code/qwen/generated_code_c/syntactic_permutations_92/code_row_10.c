#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[50];
    char password[100];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter your username: ");
    scanf("%49s", username);

    printf("Enter your password: ");
    scanf("%99s", password);

    hash_password(password, hash);
    printf("Hashed password: ");
    print_hash(hash);

    return 0;
}