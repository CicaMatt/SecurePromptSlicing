#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Here you would insert the username and hashed password into your storage
    // For demonstration, we're just printing them

    return 0;
}
