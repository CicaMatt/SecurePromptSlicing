#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char hash[HASH_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void print_hash(const unsigned char hash[HASH_LENGTH]) {
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashed_password[HASH_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    hash_password(password, hashed_password);

    printf("Hashed Password: ");
    print_hash(hashed_password);

    // Here you would typically insert the username and hashed_password into a database
    // For this example, we just print them out

    return 0;
}
