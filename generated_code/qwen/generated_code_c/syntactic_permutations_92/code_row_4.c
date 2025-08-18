#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char hashed_output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_output, &sha256);
}

void print_hash(unsigned char hashed_output[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_output[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter your username: ");
    scanf("%99s", username);

    printf("Enter your password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);
    printf("Hashed Password: ");
    print_hash(hashed_password);

    return 0;
}