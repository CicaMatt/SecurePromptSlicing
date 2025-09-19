#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Mock function to simulate database insertion
int insert_into_database(const char *username, const char *hashed_password) {
    printf("Inserting %s with hashed password %s into the database...\n", username, hashed_password);
    return 1; // Return 1 for success
}

void hash_password(const unsigned char *password, unsigned char *output_hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen((const char *)password));
    SHA256_Final(output_hash, &sha256);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0'; // Remove trailing newline
        }
    }

    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0'; // Remove trailing newline
        }
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password((unsigned char *)password, hashed_password);

    char hashed_password_str[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password_str[i * 2], "%02x", hashed_password[i]);
    }
    hashed_password_str[2 * SHA256_DIGEST_LENGTH] = '\0';

    if (insert_into_database(username, hashed_password_str)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}
 

**Note**: You need OpenSSL installed on your system to compile this program. Use `gcc -o program_name program.c -lcrypto` to compile, where `program.c` is the name of your source file.