#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define SALT_LENGTH 16

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    int len = strlen(password) + SALT_LENGTH;
    char *salted_password = malloc(len + 1);
    snprintf(salted_password, len + 1, "%s%s", password, salt);
    SHA256((const unsigned char *)salted_password, len, output);
    free(salted_password);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char salt[SALT_LENGTH + 1];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    // Simulate storing the username and hashed password with salt in a database
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(db, "%s:%s:", username, salt);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        fprintf(db, "%02x", hashed_password[i]);
    }
    fprintf(db, "\n");
    fclose(db);

    printf("Registration successful!\n");

    return 0;
}