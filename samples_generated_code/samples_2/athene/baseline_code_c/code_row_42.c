#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USER 256
#define MAX_PASS 1024

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    // Simulate database insertion
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);

    printf("Registration successful!\n");
    return EXIT_SUCCESS;
}