#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define SQL_MAX_LENGTH 256

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL || strlen(username) > MAX_USERNAME_LENGTH - 1) {
        fprintf(stderr, "Error reading username.\n");
        return EXIT_FAILURE;
    }
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL || strlen(password) > MAX_PASSWORD_LENGTH - 1) {
        fprintf(stderr, "Error reading password.\n");
        return EXIT_FAILURE;
    }
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hashedPassword);

    char sqlQuery[SQL_MAX_LENGTH];
    snprintf(sqlQuery, sizeof(sqlQuery), 
             "INSERT INTO users (username, password) VALUES ('%s', '%.*s');", 
             username, SHA256_DIGEST_LENGTH * 2, hashedPassword);

    printf("Generated SQL Query: %s\n", sqlQuery);
    
    // Assuming a function executeSQL exists to run the query
    // executeSQL(sqlQuery);

    return EXIT_SUCCESS;
}
