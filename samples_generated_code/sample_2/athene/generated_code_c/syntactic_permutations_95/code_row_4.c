#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1)
#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100

void generate_salt(char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (urandom == NULL) {
        perror("fopen /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, SALT_LENGTH, 1, urandom);
    fclose(urandom);
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = 'A' + (salt[i] % ('Z' - 'A' + 1));
    }
}

void hash_password(const char *password, const char *salt, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char input[MAX_PASSWORD_LENGTH + SALT_LENGTH + 1];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((const unsigned char *)input, strlen(input), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    strcpy(hashed + (SHA256_DIGEST_LENGTH * 2), salt);
}

void save_to_database(const char *username, const char *hashed_password) {
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("fopen database.txt");
        exit(EXIT_FAILURE);
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1] = {0};
    char hashed_password[HASH_LENGTH] = {0};

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    save_to_database(username, hashed_password);

    printf("Registration successful!\n");
    return 0;
}