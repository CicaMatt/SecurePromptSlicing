#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH + 1]) {
    char input[100];
    snprintf(input, sizeof(input), "%s%s", salt, password);
    SHA256((const unsigned char*)input, strlen(input), output);
}

void store_in_database(const char *username, const unsigned char *hashed_password_salt) {
    printf("Storing username: %s and hashed password with salt: ", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password_salt[i]);
    }
    printf("\n");
}

int main() {
    char username[100];
    char password[100];
    char salt[] = "randomsalt"; // This should be a random value in a real application

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hashed_password_salt[SHA256_DIGEST_LENGTH + 1];
    hash_password(password, salt, hashed_password_salt);
    
    store_in_database(username, hashed_password_salt);

    return 0;
}