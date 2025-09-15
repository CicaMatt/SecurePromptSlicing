#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"

typedef struct {
    char username[50];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

int create_database() {
    FILE *file = fopen(DB_FILE, "wb");
    if (file == NULL) return -1;
    fclose(file);
    return 0;
}

int add_user(const char *username, const unsigned char *password_hash) {
    FILE *file = fopen(DB_FILE, "ab+");
    if (file == NULL) return -1;

    User user;
    strcpy(user.username, username);
    memcpy(user.password_hash, password_hash, SHA256_DIGEST_LENGTH);

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password, strlen(password), hash);

    if (create_database() == -1) {
        fprintf(stderr, "Error creating database\n");
        return 1;
    }

    if (add_user(username, hash) == -1) {
        fprintf(stderr, "Error adding user to the database\n");
        return 1;
    }

    printf("User registered successfully!\n");

    return 0;
}
