#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define SALT_LENGTH 16
#define HASHED_PASSWORD_MAX (SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1)

void generate_salt(char *salt) {
    int i;
    for (i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char combined[PASSWORD_MAX + SALT_LENGTH + 1];
    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    SHA256((const unsigned char *)combined, strlen(combined), (unsigned char *)&digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }

    strcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char salt[SALT_LENGTH + 1];
    char hashed_password[HASHED_PASSWORD_MAX];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password (with salt): %s\n", hashed_password);

    // Simulate storing in a database
    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    return 0;
}