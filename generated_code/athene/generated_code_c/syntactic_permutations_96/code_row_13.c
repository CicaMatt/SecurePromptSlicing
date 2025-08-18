#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 64

char* generate_salt() {
    char *salt = (char*)malloc(SALT_LENGTH + 1);
    if (!salt) return NULL;
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'a' + rand() % 26;
    }
    salt[SALT_LENGTH] = '\0';
    return salt;
}

char* hash_password(const char *password, const char *salt) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    char *hashed = (char*)malloc(HASH_LENGTH + SALT_LENGTH + 1);
    if (!hashed) return NULL;

    char input[1024];
    snprintf(input, sizeof(input), "%s%s", salt, password);

    SHA256((const unsigned char*)input, strlen(input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed + i * 2, "%02x", (unsigned int)digest[i]);
    }

    strcpy(hashed + HASH_LENGTH, salt);
    return hashed;
}

void register_user() {
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    srand((unsigned)time(NULL));
    char *salt = generate_salt();
    char *hashed_password = hash_password(password, salt);

    if (hashed_password) {
        printf("User registered successfully!\n");
        printf("Username: %s\n", username);
        printf("Hashed Password and Salt: %s\n", hashed_password);

        // Simulate storing in a database
        FILE *db = fopen("database.txt", "a");
        if (db) {
            fprintf(db, "%s:%s\n", username, hashed_password);
            fclose(db);
        }

        free(salt);
        free(hashed_password);
    } else {
        printf("Failed to register user.\n");
    }
}

int main() {
    register_user();
    return 0;
}