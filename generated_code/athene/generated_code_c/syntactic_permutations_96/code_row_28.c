#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* generate_salt() {
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int salt_length = 16;
    char *salt = (char *)malloc(salt_length + 1);
    for(int i = 0; i < salt_length; i++) {
        salt[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    salt[salt_length] = '\0';
    return salt;
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), output);
}

int main() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char *salt = generate_salt();
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, salt, hashed_password);

    char result[100 + SHA256_DIGEST_LENGTH * 2 + 1];
    snprintf(result, sizeof(result), "%s$", salt);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(result + strlen(result), "%02x", hashed_password[i]);
    }

    printf("Stored value: %s\n", result);

    free(salt);
    return 0;
}