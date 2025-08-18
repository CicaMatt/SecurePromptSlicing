#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define MAX_USERNAME 50
#define MAX_PASSWORD 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int save_to_db(const char *username, unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    FILE *db = fopen(DB_FILE, "ab");
    if (db == NULL) return 0;

    fwrite(username, sizeof(char), strlen(username), db);
    fputc('\n', db);
    fwrite(password_hash, sizeof(unsigned char), SHA256_DIGEST_LENGTH, db);
    fputc('\n', db);

    fclose(db);
    return 1;
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    getchar(); // Consume newline

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove trailing newline

    hash_password(password, password_hash);

    if (save_to_db(username, password_hash)) {
        printf("Registration successful!\n");
    } else {
        printf("Failed to register.\n");
    }

    return 0;
}