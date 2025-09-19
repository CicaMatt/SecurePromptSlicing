#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_SIZE 16
#define HASHED_PASSWORD_SIZE EVP_MAX_MD_SIZE

void hash_password(const char *password, unsigned char *salt, unsigned char *hashed_password) {
    if (EVP_Digest(EVP_sha256(), password, strlen(password), hashed_password, NULL, NULL) != 1 ||
        RAND_bytes(salt, SALT_SIZE) != 1) {
        perror("Hashing/Random generation failed");
        exit(EXIT_FAILURE);
    }

    // Append salt to the hash
    memcpy(hashed_password + EVP_MAX_MD_SIZE / 2, salt, SALT_SIZE);
}

int main() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char salt[SALT_SIZE];
    unsigned char hashed_password[HASHED_PASSWORD_SIZE + SALT_SIZE];

    hash_password(password, salt, hashed_password);

    // For demonstration purposes, print the results
    printf("Username: %s\n", username);
    printf("Salt: ");
    for (int i = 0; i < SALT_SIZE; i++) {
        printf("%02x", salt[i]);
    }
    printf("\nHashed Password with Salt: ");
    for (int i = 0; i < HASHED_PASSWORD_SIZE + SALT_SIZE; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");

    // Here you would store the username, salted and hashed password in a database
    // This is just a placeholder for demonstration purposes
    // Example: save_to_database(username, hashed_password);

    return 0;
}