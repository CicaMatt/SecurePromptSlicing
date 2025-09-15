#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void hash_password(const char *input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[MAX_USERNAME_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    hash_password(password, hashed_password);

    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Simulate database insertion
    // In a real application, use an appropriate library to connect to your database
    // and execute the SQL query with prepared statements to avoid SQL injection.
    // Here we just simulate it by printing.

    printf("Inserting into database...\n");
    printf("INSERT INTO users (username, password) VALUES ('%s', '%.*s');\n",
           username,
           SHA256_DIGEST_LENGTH * 2,
           hashed_password);

    return 0;
}
