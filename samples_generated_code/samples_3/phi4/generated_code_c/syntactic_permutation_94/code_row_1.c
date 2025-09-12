#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

void hash_password(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

int insert_into_database(const char *username, const unsigned char *hashed_password) {
    // Dummy function to simulate database insertion
    printf("Inserting into database:\n");
    printf("Username: %s\n", username);
    printf("Hashed Password: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Simulate successful insertion
    return 1;
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME_LEN, stdin) == NULL || strlen(username) <= 0 ||
        username[strlen(username) - 1] != '\n') {
        fprintf(stderr, "Error reading username.\n");
        return 1;
    }
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD_LEN, stdin) == NULL || strlen(password) <= 0 ||
        password[strlen(password) - 1] != '\n') {
        fprintf(stderr, "Error reading password.\n");
        return 1;
    }
    password[strcspn(password, "\n")] = '\0';

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    if (insert_into_database(username, hashed_password)) {
        printf("Insertion successful.\n");
    } else {
        fprintf(stderr, "Failed to insert into database.\n");
    }

    return 0;
}