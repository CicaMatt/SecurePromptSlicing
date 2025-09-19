#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"

typedef struct {
    char username[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
} User;

void hash_password(const char *password, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int insert_user_into_db(const User *user) {
    FILE *file = fopen(DB_FILE, "ab");
    if (!file) {
        perror("Failed to open database file");
        return -1;
    }

    size_t written = fwrite(user, sizeof(User), 1, file);
    fclose(file);

    return (written == 1) ? 0 : -1;
}

int main() {
    User user;
    char password[100];

    printf("Enter username: ");
    scanf("%99s", user.username); // Limit input to prevent buffer overflow

    printf("Enter password: ");
    scanf("%99s", password);

    hash_password(password, user.hashed_password);
    
    if (insert_user_into_db(&user) == 0) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Failed to register user.\n");
    }

    return 0;
}