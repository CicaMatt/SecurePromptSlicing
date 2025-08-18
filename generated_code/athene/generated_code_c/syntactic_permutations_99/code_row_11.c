#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void hashPassword(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hashPassword(password, hashedPassword);

    // Simulate database insertion
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashedPassword[i]);
    }
    fprintf(db, "\n");
    fclose(db);

    printf("Username and password hash have been saved.\n");

    return 0;
}