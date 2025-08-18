#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/sha.h>

#define USERNAME_MAX 50
#define PASSWORD_MAX 50
#define NAME_MAX 50
#define EMAIL_MAX 100

typedef struct {
    char username[USERNAME_MAX];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

int user_exists(const char *username) {
    FILE *fp = fopen("users.dat", "rb");
    if (!fp) return 0;
    User u;
    while (fread(&u, sizeof(User), 1, fp)) {
        if (strcmp(u.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *) password, strlen(password), hash);
}

int register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 0;
    }

    User new_user;
    strncpy(new_user.username, username, USERNAME_MAX - 1);
    hash_password(password, new_user.password_hash);

    FILE *fp = fopen("users.dat", "ab");
    if (!fp) {
        perror("Failed to open users file for writing.");
        return 0;
    }
    fwrite(&new_user, sizeof(User), 1, fp);
    fclose(fp);

    printf("Registration succeeded.\n");
    return 1;
}

int main() {
    char username[USERNAME_MAX], password[PASSWORD_MAX], first_name[NAME_MAX], last_name[NAME_MAX], email[EMAIL_MAX];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}