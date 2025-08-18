#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH + 1]) {
    char salted_password[100];
    snprintf(salted_password, sizeof(salted_password), "%s%s", salt, password);
    SHA256((unsigned char *)salted_password, strlen(salted_password), output);
}

void save_to_database(const char *username, const unsigned char *hashed_password) {
    printf("Saving to database:\n");
    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    char salt[] = "random_salt"; // In a real application, this should be generated securely and uniquely per user

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH + 1];
    hash_password(password, salt, hashed_password);
    save_to_database(username, hashed_password);

    return 0;
}