#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 100
#define SALT_LEN 16

void generate_salt(char *salt, size_t len) {
    srand(time(NULL));
    for (int i = 0; i < len; i++) {
        salt[i] = 32 + rand() % 95;
    }
    salt[len] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LEN);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password_with_salt) {
    // Simulate storing in a database
    FILE *db = fopen("user_db.txt", "a");
    if (db == NULL) {
        perror("Failed to open user database file");
        return;
    }
    fprintf(db, "%s:%s\n", username, hashed_password_with_salt);
    fclose(db);
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char salt[SALT_LEN + 1];
    char hashed_password_with_salt[(SHA256_DIGEST_LENGTH * 2) + SALT_LEN + 1];

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt, SALT_LEN);

    hash_password(password, salt, hashed_password_with_salt);

    strncat(hashed_password_with_salt, salt, SALT_LEN);

    store_in_database(username, hashed_password_with_salt);

    printf("Registration successful!\n");

    return 0;
}