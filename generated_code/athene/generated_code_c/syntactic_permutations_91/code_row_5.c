#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USER 50
#define MAX_PASS 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_user(const char *username, const unsigned char *password_hash) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) return 0;

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", password_hash[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USER];
    char password[MAX_PASS];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    if (save_user(username, password_hash)) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
        return 1;
    }

    return 0;
}