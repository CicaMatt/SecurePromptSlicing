#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USER 100
#define MAX_PASS 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_to_db(const char *username, const unsigned char *hashed_password) {
    FILE *db = fopen(DB_FILE, "a");
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
    char username[MAX_USER];
    char password[MAX_PASS];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, hashed_password);

    if (save_to_db(username, hashed_password)) {
        printf("User saved successfully.\n");
    } else {
        printf("Failed to save user.\n");
    }

    return 0;
}