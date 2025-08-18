#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int main() {
    char username[MAX_USERNAME + 1];
    char password[MAX_PASSWORD + 1];
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
        perror("Failed to open database file");
        return 1;
    }

    fprintf(db, "%s:%x", username, *(unsigned int *)hashed_password);
    for (int i = 4; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);

    printf("Registration successful!\n");
    return 0;
}