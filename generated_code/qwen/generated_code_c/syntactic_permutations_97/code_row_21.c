#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

int user_exists(const char* username) {
    FILE* file = fopen("users.dat", "rb");
    if (!file) return 0;

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void hash_password(const char* password, char* hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void register_user(const char* username, const char* password) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    User new_user;
    strncpy(new_user.username, username, MAX_USERNAME_LENGTH);
    hash_password(password, new_user.hashed_password);

    FILE* file = fopen("users.dat", "ab");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fwrite(&new_user, sizeof(User), 1, file);
    fclose(file);

    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    register_user(username, password);

    return 0;
}