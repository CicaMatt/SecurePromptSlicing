#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    char input[MAX_PASSWORD_LENGTH + SALT_LENGTH + 1];

    strcpy(input, password);
    strcat(input, salt);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(sha256_hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", sha256_hash[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void store_in_database(const char *username, const char *salted_hashed_password) {
    FILE *db = fopen("user_data.txt", "a");
    if (db == NULL) {
        perror("Error opening database file");
        return;
    }
    fprintf(db, "%s:%s\n", username, salted_hashed_password);
    fclose(db);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];

    printf("Enter your username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    generate_salt(salt);
    hash_password(password, salt, hashed_password);
    strcat(hashed_password, salt);

    store_in_database(username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}