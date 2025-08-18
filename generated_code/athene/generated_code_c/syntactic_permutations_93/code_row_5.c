#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50
#define HASHED_PASSWORD_LENGTH 65

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed_password[HASHED_PASSWORD_LENGTH - 1] = '\0';
}

void insert_into_database(const char *username, const char *hashed_password) {
    FILE *fp;
    fp = fopen("users.db", "a");
    if (!fp) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s:%s\n", username, hashed_password);
    fclose(fp);
}

int main() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char hashed_password[HASHED_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);
    insert_into_database(username, hashed_password);

    printf("User registered successfully.\n");

    return 0;
}