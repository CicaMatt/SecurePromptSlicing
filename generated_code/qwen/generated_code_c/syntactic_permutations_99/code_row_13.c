#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    char username[100];
    char password[100];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);

    return 0;
}