#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    char name[100];
    char password[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    printf("Registration successful!\n");
    printf("Name: %s\n", name);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}