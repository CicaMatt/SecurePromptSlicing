#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    char input[256];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)input, strlen(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        snprintf(hashed_password + (i * 2), HASH_LENGTH - (i * 2) + 1, "%02x", hash[i]);
    }
}

void save_to_database(const char *username, const char *hashed_password_with_salt) {
    FILE *file = fopen("users.db", "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s:%s\n", username, hashed_password_with_salt);
    fclose(file);
}

int main() {
    srand(time(NULL));

    char username[100];
    char password[100];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASH_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    snprintf(hashed_password + HASH_LENGTH, SALT_LENGTH + 1, "%s", salt);

    save_to_database(username, hashed_password);

    printf("Registration successful.\n");
    return 0;
}