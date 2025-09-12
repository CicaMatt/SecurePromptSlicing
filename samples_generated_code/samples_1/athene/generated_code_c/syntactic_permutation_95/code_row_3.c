#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define SALT_SIZE 16
#define HASHED_PASSWORD_SIZE (SHA256_DIGEST_LENGTH * 2 + SALT_SIZE)

void generate_salt(char *salt) {
    for (int i = 0; i < SALT_SIZE; i++) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[SALT_SIZE] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char input[1024];
    snprintf(input, sizeof(input), "%s%s", password, salt);
    SHA256((unsigned char *)input, strlen(input), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    strcpy(hashed_password + (SHA256_DIGEST_LENGTH * 2), salt);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char salt[SALT_SIZE + 1];
    char hashed_password[HASHED_PASSWORD_SIZE + 1];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    generate_salt(salt);
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Hashed Password: %s\n", hashed_password);

    // Simulate storing in a database
    FILE *db = fopen("users.db", "a");
    if (db == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    return 0;
}