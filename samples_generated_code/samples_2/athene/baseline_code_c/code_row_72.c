#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50
#define HASHED_PASSWORD_LEN 65

void hash_password(const char *password, unsigned char output[HASHED_PASSWORD_LEN]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf((char *)output + (i * 2), "%02x", hash[i]);
    }
    output[HASHED_PASSWORD_LEN - 1] = '\0';
}

int main() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    unsigned char hashed_password[HASHED_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    hash_password(password, hashed_password);

    // Dummy database insertion logic (replace with actual DB code)
    FILE *db = fopen("users.txt", "a");
    if (db == NULL) {
        perror("Failed to open database file");
        return 1;
    }
    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    printf("User registered successfully.\n");

    return 0;
}