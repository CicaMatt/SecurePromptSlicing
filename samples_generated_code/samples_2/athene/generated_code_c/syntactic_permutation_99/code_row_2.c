#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

void hash_password(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_LENGTH - 1] = '\0';
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char hashed_password[HASH_LENGTH];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX, stdin);
    password[strcspn(password, "\n")] = 0;

    hash_password(password, hashed_password);

    FILE *db = fopen("database.txt", "a");
    if (db == NULL) {
        perror("Error opening database file");
        return 1;
    }

    fprintf(db, "%s:%s\n", username, hashed_password);
    fclose(db);

    printf("User registered successfully.\n");

    return 0;
}