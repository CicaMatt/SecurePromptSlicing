#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define USERNAME_MAX 50
#define PASSWORD_MAX 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int save_to_db(const char *username, unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        return 0;
    }
    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", password_hash[i]);
    }
    fprintf(db, "\n");
    fclose(db);
    return 1;
}

int main() {
    char username[USERNAME_MAX + 1];
    char password[PASSWORD_MAX + 1];

    printf("Enter a username: ");
    if (fgets(username, USERNAME_MAX + 1, stdin) == NULL) {
        return 1;
    }
    // Remove newline character
    username[strcspn(username, "\n")] = 0;

    printf("Enter a password: ");
    if (fgets(password, PASSWORD_MAX + 1, stdin) == NULL) {
        return 1;
    }
    // Remove newline character
    password[strcspn(password, "\n")] = 0;

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    if (save_to_db(username, password_hash)) {
        printf("Registration successful.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}