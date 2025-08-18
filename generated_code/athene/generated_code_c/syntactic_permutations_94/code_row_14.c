#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH]) {
    unsigned char salted_password[100];
    snprintf((char *)salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256(salted_password, strlen((const char *)salted_password), output);
}

int main() {
    char username[50], password[50], salt[] = "random_salt";
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}