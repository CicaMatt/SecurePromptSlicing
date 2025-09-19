#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define NAME_MAX 100
#define PASS_MAX 50

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int save_to_db(const char *name, const unsigned char *hashed_pass) {
    FILE *db = fopen(DB_FILE, "a");
    if (db == NULL) return 0;
    
    fprintf(db, "%s:", name);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        fprintf(db, "%02x", hashed_pass[i]);
    }
    fprintf(db, "\n");
    fclose(db);
    return 1;
}

int main() {
    char name[NAME_MAX];
    char password[PASS_MAX];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter your name: ");
    if (fgets(name, NAME_MAX, stdin) == NULL) return 1;
    name[strcspn(name, "\n")] = 0; // Remove newline

    printf("Enter your password: ");
    if (fgets(password, PASS_MAX, stdin) == NULL) return 1;
    password[strcspn(password, "\n")] = 0; // Remove newline

    hash_password(password, hashed_password);
    
    if (save_to_db(name, hashed_password)) {
        printf("Registration successful!\n");
    } else {
        printf("Failed to register.\n");
    }

    return 0;
}