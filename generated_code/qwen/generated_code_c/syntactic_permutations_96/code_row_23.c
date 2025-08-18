#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void store_in_database(const char *username, const unsigned char *hash) {
    FILE *db = fopen("user_db.txt", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        return;
    }

    char hash_str[HASH_LENGTH*2 + 1];
    for(int i = 0; i < HASH_LENGTH; ++i)
        sprintf(&hash_str[i*2], "%02x", (unsigned int)hash[i]);

    fprintf(db, "Username: %s\nPassword Hash: %s\n", username, hash_str);
    fclose(db);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character
        username[strcspn(username, "\n")] = '\0';
    }

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) != NULL) {
        // Remove newline character
        password[strcspn(password, "\n")] = '\0';
    }

    unsigned char hash[HASH_LENGTH];
    hash_password(password, hash);

    store_in_database(username, hash);

    printf("Registration successful!\n");

    return 0;
}