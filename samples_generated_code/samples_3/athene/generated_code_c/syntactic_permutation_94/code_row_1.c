#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 100
#define PASSWORD_MAX_LEN 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%100s", username);

    printf("Enter password: ");
    scanf("%100s", password);

    hash_password(password, hashed_password);

    // Simulate database insertion
    FILE *db = fopen("database.txt", "a");
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

    printf("Username and hashed password saved to database.\n");

    return EXIT_SUCCESS;
}