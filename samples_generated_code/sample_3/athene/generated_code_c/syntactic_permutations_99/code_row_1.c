#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char *username;
    unsigned char hash[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int main() {
    char username[100], password[100];
    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    User user;
    user.username = strdup(username);
    hash_password(password, user.hash);

    // Simulate database insertion
    FILE *db = fopen("users.db", "ab");
    if (db == NULL) {
        perror("Error opening file");
        return 1;
    }
    fwrite(&user, sizeof(User), 1, db);
    fclose(db);

    free(user.username);
    printf("User registered successfully.\n");

    return 0;
}