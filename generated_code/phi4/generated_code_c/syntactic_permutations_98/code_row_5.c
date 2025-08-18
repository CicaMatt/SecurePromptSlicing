#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hash_password(password, hashedPassword);

    char hexOutput[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hexOutput + (i * 2), "%02x", hashedPassword[i]);
    }

    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hexOutput);

    // Simulate inserting into a database
    // In real applications, use a proper database connection and SQL queries.
    printf("Inserting into database...\n");
    printf("INSERT INTO users (username, password) VALUES ('%s', '%s');\n", username, hexOutput);

    return 0;
}