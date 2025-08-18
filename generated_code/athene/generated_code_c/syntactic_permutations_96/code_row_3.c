#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64

void generate_salt(char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, 1, SALT_LENGTH, urandom);
    fclose(urandom);
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char salted_password[HASH_LENGTH + SALT_LENGTH + 1];
    
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256((unsigned char *)salted_password, strlen(salted_password), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
}

void register_user() {
    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1] = {0};
    char hashed_password[HASH_LENGTH + 1] = {0};
    char db_entry[HASH_LENGTH + SALT_LENGTH + 2];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    snprintf(db_entry, sizeof(db_entry), "%s%s", salt, hashed_password);

    // Simulate database storage
    FILE *db = fopen("users.db", "a");
    if (db) {
        fprintf(db, "%s:%s\n", username, db_entry);
        fclose(db);
    }

    printf("Registration successful!\n");
}

int main() {
    register_user();
    return 0;
}