#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char *password, const char *salt, char outputBuffer[128]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    int i;
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    strcat(outputBuffer, salt);
}

int main() {
    char username[100];
    char password[100];
    const char *salt = "somesalt";
    char storedPassword[128];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, salt, storedPassword);

    printf("Username: %s\n", username);
    printf("Stored Password (hash + salt): %s\n", storedPassword);

    // Normally here you would store the username and hashed password in a database
    return 0;
}