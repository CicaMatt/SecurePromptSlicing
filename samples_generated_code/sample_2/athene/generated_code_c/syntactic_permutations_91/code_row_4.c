#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 256
#define MAX_PASSWORD 256

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME, stdin) == NULL) return 1;
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD, stdin) == NULL) return 1;
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    FILE *db = fopen("users.db", "a");
    if (!db) {
        perror("Failed to open database file");
        return 1;
    }

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);

    printf("Registration successful!\n");
    return 0;
}