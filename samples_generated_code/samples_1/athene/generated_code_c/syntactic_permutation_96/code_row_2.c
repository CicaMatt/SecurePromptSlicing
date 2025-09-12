#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((char *)output + (i * 2), "%02x", hash[i]);
    }
}

void register_user() {
    char username[100];
    char password[100];
    char salt[] = "random_salt"; // This should be a random value in production
    unsigned char hashed_password[65]; // SHA256_DIGEST_LENGTH * 2 + 1 for null terminator

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, salt, hashed_password);
    printf("Salted and Hashed Password: %s\n", hashed_password);

    // Simulate storing the username and salted hashed password in a database
    printf("Storing user '%s' with hashed password '%s' in the database.\n", username, hashed_password);
}

int main() {
    register_user();
    return 0;
}