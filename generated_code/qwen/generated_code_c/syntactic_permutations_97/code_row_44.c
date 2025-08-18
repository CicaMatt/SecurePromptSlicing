#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_NAME 50
#define MAX_EMAIL 100

typedef struct {
    char username[MAX_USERNAME];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
} User;

int user_exists(const char* username) {
    FILE* fp = fopen("users.dat", "rb");
    if (!fp) return 0;

    User user;
    while (fread(&user, sizeof(User), 1, fp)) {
        if (strcmp(user.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
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
}

void register_user(const char* username, const char* password) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    User user;
    strncpy(user.username, username, MAX_USERNAME);
    hash_password(password, user.hashed_password);

    FILE* fp = fopen("users.dat", "ab");
    if (!fp) {
        perror("Failed to open file");
        return;
    }
    fwrite(&user, sizeof(User), 1, fp);
    fclose(fp);

    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Email: ");
    scanf("%s", email);

    register_user(username, password);

    return 0;
}