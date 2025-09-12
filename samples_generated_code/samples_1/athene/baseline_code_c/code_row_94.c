#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define DB_FILE "users.db"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int save_to_db(const char *username, const unsigned char *hashed_password) {
    FILE *db = fopen(DB_FILE, "a");
    if (!db) return 0;
    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");
    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USERNAME + 1];
    char password[MAX_PASSWORD + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    hash_password(password, hashed_password);
    if (save_to_db(username, hashed_password)) {
        printf("Registration successful.\n");
    } else {
        printf("Failed to save user data.\n");
    }

    return 0;
}