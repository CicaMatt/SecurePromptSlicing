#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100

void hashPassword(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), outputBuffer);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hashPassword(password, hashedPassword);

    // Simulate database insertion (in a real scenario, use a proper DB connection and prepared statements)
    printf("INSERT INTO users (username, password) VALUES ('%s', '", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashedPassword[i]);
    }
    printf("');\n");

    return 0;
}