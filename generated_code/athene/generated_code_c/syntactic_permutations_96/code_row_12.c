#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)
#define BUFFER_SIZE 256

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + (rand() % ('Z' - 'A' + 1));
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[BUFFER_SIZE];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed[HASH_LENGTH - 1] = '\0';
}

void register_user(char *username, char *password) {
    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hashed_password[HASH_LENGTH];
    hash_password(password, salt, hashed_password);

    char db_entry[BUFFER_SIZE];
    snprintf(db_entry, sizeof(db_entry), "%s:%s$%s", username, salt, hashed_password);

    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s\n", db_entry);
    fclose(db);
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    register_user(username, password);

    printf("User registered successfully.\n");
    return 0;
}