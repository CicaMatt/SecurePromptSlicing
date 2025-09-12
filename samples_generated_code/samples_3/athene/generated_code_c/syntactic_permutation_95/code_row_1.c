#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)
#define BUFFER_SIZE 256

void generate_salt(char *salt, size_t length) {
    for (size_t i = 0; i < length - 1; ++i) {
        salt[i] = 'A' + rand() % ('Z' - 'A' + 1);
    }
    salt[length - 1] = '\0';
}

void hash_password(const char *password, const char *salt, char *hashed_password) {
    char input[BUFFER_SIZE];
    snprintf(input, sizeof(input), "%s%s", password, salt);

    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)input, strlen(input), digest);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", (unsigned int)digest[i]);
    }
    hashed_password[HASH_LENGTH - 1] = '\0';
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    char salt[SALT_LENGTH];
    char hashed_password[HASH_LENGTH];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    generate_salt(salt, SALT_LENGTH);
    hash_password(password, salt, hashed_password);

    printf("Username: %s\n", username);
    printf("Salt: %s\n", salt);
    printf("Hashed Password: %s\n", hashed_password);

    // Simulate storing in a database
    FILE *db = fopen("user_db.txt", "a");
    if (db == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(db, "%s:%s:%s\n", username, salt, hashed_password);
    fclose(db);

    return 0;
}