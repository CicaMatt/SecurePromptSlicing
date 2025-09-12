#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Mock function to simulate inserting into a database.
int insert_into_db(const char *username, const unsigned char *hashed_password) {
    printf("Inserting into DB: Username=%s, Hashed Password=", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
    return 1; // Simulating successful insertion.
}

void hash_password(const char *password, unsigned char *output_hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output_hash, &sha256);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    if (insert_into_db(username, hashed_password)) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    return 0;
}