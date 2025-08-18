#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} UserCredentials;

int insert_into_database(UserCredentials *user) {
    // Dummy function for database insertion; replace with actual database code.
    printf("Inserting into database: Username=%s, Hash=", user->username);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", user->hash[i]);
    }
    printf("\n");
    return 1; // Simulate successful insertion.
}

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    UserCredentials user;
    printf("Enter username: ");
    if (fgets(user.username, MAX_USERNAME_LEN, stdin) == NULL || strchr(user.username, '\n') == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    user.username[strcspn(user.username, "\n")] = 0; // Remove newline character.

    printf("Enter password: ");
    if (fgets((char *)user.hash, MAX_PASSWORD_LEN + 1, stdin) == NULL || strchr((char *)user.hash, '\n') == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    user.hash[strcspn((char *)user.hash, "\n")] = 0; // Remove newline character.

    hash_password(user.hash, user.hash);

    if (!insert_into_database(&user)) {
        fprintf(stderr, "Failed to insert into database.\n");
        return 1;
    }

    printf("User added successfully.\n");
    return 0;
}