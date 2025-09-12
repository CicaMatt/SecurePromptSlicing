#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

void store_in_database(const char *username, const unsigned char *hashed_password) {
    // Simulate storing in a database
    printf("Storing username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, hashed_password);
    store_in_database(username, hashed_password);

    return 0;
}