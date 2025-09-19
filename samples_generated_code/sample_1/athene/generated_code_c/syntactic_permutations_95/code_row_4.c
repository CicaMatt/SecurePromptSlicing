#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % 26;
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char temp[MAX_PASSWORD + SALT_LENGTH + 1];
    snprintf(temp, sizeof(temp), "%s%s", salt, password);
    SHA256((const unsigned char *)temp, strlen(temp), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", digest[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void store_to_database(const char *username, const char *salted_hash) {
    FILE *fp = fopen("users.db", "a");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s:%s\n", username, salted_hash);
    fclose(fp);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char salted_hash[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];

    srand(time(NULL));

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    snprintf(salted_hash, sizeof(salted_hash), "%s%s", salt, hashed_password);

    store_to_database(username, salted_hash);

    printf("Registration successful!\n");

    return 0;
}