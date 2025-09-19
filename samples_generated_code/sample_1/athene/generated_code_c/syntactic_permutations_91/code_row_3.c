#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int save_user_to_db(const char *username, const unsigned char *hashed_password) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) {
        return 0;
    }
    fprintf(db, "%s:", username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");
    fclose(db);
    return 1;
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    if (fgets(username, BUFFER_SIZE, stdin) == NULL) {
        return EXIT_FAILURE;
    }
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    if (fgets(password, BUFFER_SIZE, stdin) == NULL) {
        return EXIT_FAILURE;
    }
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    if (save_user_to_db(username, hashed_password)) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return EXIT_SUCCESS;
}