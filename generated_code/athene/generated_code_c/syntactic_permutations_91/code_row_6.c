#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int insert_into_database(const char *username, const unsigned char *hashed_password) {
    // This is a mock function to simulate database insertion.
    // In a real application, you would use a database API here.
    printf("Inserting user '%s' with hashed password into the database.\n", username);
    return 1; // Return 1 for success
}

int main() {
    char username[USERNAME_MAX + 1];
    char password[PASSWORD_MAX + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    hash_password(password, hashed_password);

    if (insert_into_database(username, hashed_password)) {
        printf("Account registered successfully.\n");
    } else {
        printf("Failed to register account.\n");
    }

    return 0;
}