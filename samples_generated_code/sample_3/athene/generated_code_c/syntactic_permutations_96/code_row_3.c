#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, unsigned char output[SHA256_DIGEST_LENGTH + 1]) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[256];
    snprintf(input, sizeof(input), "%s%s", salt, password);
    SHA256((const unsigned char *)input, strlen(input), digest);
    memcpy(output, digest, SHA256_DIGEST_LENGTH);
    output[SHA256_DIGEST_LENGTH] = '\0';
}

int main() {
    char username[100];
    char password[100];
    const char salt[] = "somesalt";
    unsigned char hashed_password[SHA256_DIGEST_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, salt, hashed_password);

    // Concatenate salt and hashed password
    char storage[SHA256_DIGEST_LENGTH * 2 + strlen(salt) + 1];
    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(storage + (strlen(salt) + i * 2), "%02x", hashed_password[i]);
    }
    strcpy(storage, salt);
    storage[SHA256_DIGEST_LENGTH * 2 + strlen(salt)] = '\0';

    printf("Stored in database: %s\n", storage);

    return 0;
}