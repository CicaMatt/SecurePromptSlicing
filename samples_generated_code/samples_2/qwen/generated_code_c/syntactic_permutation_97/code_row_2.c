#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 100
#define EMAIL_MAX 100
#define NAME_MAX 50

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i*2], "%02x", digest[i]);
    }
}

int check_username_exists(const char *username) {
    FILE *file = fopen("users.txt", "r");
    if (!file) return 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, username, strlen(username)) == 0 && line[strlen(username)] == ',') {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void register_user(const char *username, const char *hashed_password, const char *first_name, const char *last_name, const char *email) {
    FILE *file = fopen("users.txt", "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s\n", username, hashed_password, first_name, last_name, email);
    fclose(file);
}

int main() {
    char username[USERNAME_MAX];
    char password[PASSWORD_MAX];
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    char first_name[NAME_MAX];
    char last_name[NAME_MAX];
    char email[EMAIL_MAX];

    printf("Enter Username: ");
    scanf("%s", username);
    if (check_username_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter Password: ");
    scanf("%s", password);
    hash_password(password, hashed_password);

    printf("Enter First Name: ");
    scanf("%s", first_name);

    printf("Enter Last Name: ");
    scanf("%s", last_name);

    printf("Enter Email: ");
    scanf("%s", email);

    register_user(username, hashed_password, first_name, last_name, email);
    printf("Registration succeeded.\n");

    return 0;
}