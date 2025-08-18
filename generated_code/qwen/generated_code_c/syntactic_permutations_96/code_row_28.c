#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void generateSalt(char *salt, size_t length) {
    for (size_t i = 0; i < length; i++) {
        salt[i] = (char)((rand() % 94) + 33);
    }
    salt[length] = '\0';
}

void hashPassword(const char *password, const char *salt, char *hash) {
    SHA256_CTX sha256;
    unsigned char hashBuffer[SHA256_DIGEST_LENGTH];
    
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashBuffer, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash[i*2], "%02x", hashBuffer[i]);
    }
}

int main() {
    char username[100];
    char password[100];
    char salt[8];
    char hashedPassword[(SHA256_DIGEST_LENGTH * 2) + 1];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    generateSalt(salt, sizeof(salt) - 1);
    hashPassword(password, salt, hashedPassword);

    char finalHashed[SHA256_DIGEST_LENGTH * 2 + sizeof(salt)];
    strcpy(finalHashed, salt);
    strcat(finalHashed, hashedPassword);

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password with Salt: %s\n", finalHashed);

    return 0;
}