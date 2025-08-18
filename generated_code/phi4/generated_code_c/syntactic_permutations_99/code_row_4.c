#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Mock function to simulate database insertion
void insert_into_database(const char *username, const unsigned char *hashed_password) {
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        printf("%02x", hashed_password[i]);
    printf("\n");
}

unsigned char* hash_password(const char *password) {
    unsigned char *hashed_password = malloc(SHA256_DIGEST_LENGTH);
    if (!hashed_password) return NULL;
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);

    return hashed_password;
}

int main() {
    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    // Use getchar to consume the newline character after entering the username
    getchar(); 
    fgets(password, sizeof(password), stdin);
    // Remove newline character from password input if present
    size_t len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    unsigned char *hashed_password = hash_password(password);
    if (!hashed_password) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    insert_into_database(username, hashed_password);

    free(hashed_password);

    return EXIT_SUCCESS;
}