#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, size_t salt_length) {
    srand(time(NULL));
    for (size_t i = 0; i < salt_length; ++i) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[salt_length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char salted_password[MAX_PASSWORD_LENGTH + SALT_LENGTH + 1];
    snprintf(salted_password, sizeof(salted_password), "%s%s", password, salt);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password_with_salt) {
    FILE *db_file = fopen("user_db.txt", "a");
    if (!db_file) {
        perror("Failed to open database file");
        return;
    }
    fprintf(db_file, "%s:%s\n", username, hashed_password_with_salt);
    fclose(db_file);
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char hashed_password_with_salt[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);
    snprintf(hashed_password_with_salt, sizeof(hashed_password_with_salt), "%s%s", hashed_password, salt);

    store_in_database(username, hashed_password_with_salt);

    printf("Registration successful!\n");

    return 0;
}