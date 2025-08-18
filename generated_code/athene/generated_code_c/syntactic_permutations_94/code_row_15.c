#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH]) {
    unsigned char salted_pass[128];
    snprintf((char *)salted_pass, sizeof(salted_pass), "%s%s", password, salt);
    SHA256(salted_pass, strlen((const char *)salted_pass), output);
}

int main() {
    char username[100];
    char password[100];
    char salt[32] = "a_random_salt_string_here";
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, salt, hashed_password);

    // Output the username and hashed password (for demonstration purposes)
    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    return 0;
}