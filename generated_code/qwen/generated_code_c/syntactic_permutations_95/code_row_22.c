#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < length; i++) {
        int key = rand() % strlen(charset);
        salt[i] = charset[key];
    }
}

void hash_password(const char *password, const char *salt, char *hash) {
    unsigned char hashed[SHA256_DIGEST_LENGTH];
    char salted_password[MAX_PASSWORD_LENGTH + SALT_LENGTH + 1];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hashed, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", hashed[i]);
    }
}

void store_in_database(const char *username, const char *salted_hash) {
    // Simulate storing in a database
    FILE *db = fopen("user_db.txt", "a");
    if (db) {
        fprintf(db, "%s:%s\n", username, salted_hash);
        fclose(db);
    }
}

int main() {
    srand(time(NULL));

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1] = {0};
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1] = {0};

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    char salted_hash[SALT_LENGTH + SHA256_DIGEST_LENGTH * 2 + 1];
    snprintf(salted_hash, sizeof(salted_hash), "%s:%s", salt, hashed_password);

    store_in_database(username, salted_hash);

    printf("Registration successful!\n");

    return 0;
}