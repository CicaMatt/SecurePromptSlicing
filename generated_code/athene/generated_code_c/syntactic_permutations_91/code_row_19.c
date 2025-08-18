#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define DATABASE_FILE "users.db"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_to_database(const char *username, const unsigned char *hashed_password) {
    FILE *db = fopen(DATABASE_FILE, "a");
    if (db == NULL) return 0;

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%100s", username);

    printf("Enter password: ");
    scanf("%100s", password);

    hash_password(password, hashed_password);

    if (save_to_database(username, hashed_password)) {
        printf("Registration successful!\n");
    } else {
        printf("Failed to register.\n");
    }

    return 0;
}