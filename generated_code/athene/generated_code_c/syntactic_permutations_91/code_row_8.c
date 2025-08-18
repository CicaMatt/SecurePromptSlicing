#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DATABASE_FILE "users.db"
#define USERNAME_MAX_LEN 32
#define PASSWORD_MAX_LEN 64

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_to_database(const char *username, const unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    FILE *db = fopen(DATABASE_FILE, "a");
    if (!db) return 0;

    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");

    fclose(db);
    return 1;
}

int main() {
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];

    printf("Enter username: ");
    if (!fgets(username, USERNAME_MAX_LEN + 1, stdin)) return 1;
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    if (!fgets(password, PASSWORD_MAX_LEN + 1, stdin)) return 1;
    password[strcspn(password, "\n")] = 0;

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    if (save_to_database(username, hashed_password)) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
        return 1;
    }

    return 0;
}