#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH + 1]) {
    char salted_pass[100];
    snprintf(salted_pass, sizeof(salted_pass), "%s%s", password, salt);
    SHA256((const unsigned char *)salted_pass, strlen(salted_pass), output);
}

void store_in_database(const char *username, const unsigned char *hashed_password) {
    printf("Storing username: %s and hashed password: ", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    const char *salt = "somesalt";

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH + 1];
    hash_password(password, salt, hashed_password);
    store_in_database(username, hashed_password);

    return 0;
}