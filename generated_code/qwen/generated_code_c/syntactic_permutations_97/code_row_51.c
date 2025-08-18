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
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
} User;

int userExists(const char *username) {
    FILE *file = fopen("users.db", "rb");
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

void hashPassword(const char *password, unsigned char hashedPassword[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashedPassword, &sha256);
}

void registerUser(const char *username, const char *password) {
    if (userExists(username)) {
        printf("Username already exists.\n");
        return;
    }

    User newUser;
    strcpy(newUser.username, username);
    hashPassword(password, newUser.hashedPassword);

    FILE *file = fopen("users.db", "ab");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);

    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    registerUser(username, password);

    return 0;
}