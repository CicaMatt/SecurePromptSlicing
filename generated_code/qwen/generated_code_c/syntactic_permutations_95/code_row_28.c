#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++) {
        salt[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    salt[length] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
}

void store_in_database(const char *username, const char *hashed_password_with_salt) {
    FILE *fp = fopen("users.txt", "a");
    if (!fp) {
        perror("Failed to open database file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s:%s\n", username, hashed_password_with_salt);
    fclose(fp);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char salt[SALT_LENGTH + 1];
    char hashed_password[2 * SHA256_DIGEST_LENGTH + SALT_LENGTH + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    srand(time(NULL));
    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);
    strncat(hashed_password, salt, SALT_LENGTH);

    store_in_database(username, hashed_password);

    printf("Registration successful!\n");

    return 0;
}