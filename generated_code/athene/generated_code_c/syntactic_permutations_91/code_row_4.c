#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100

void hashPassword(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hashPassword(password, hashedPassword);

    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Error opening database file");
        return EXIT_FAILURE;
    }

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashedPassword[i]);
    }
    fprintf(db, "\n");

    fclose(db);

    printf("User registration successful.\n");
    return EXIT_SUCCESS;
}