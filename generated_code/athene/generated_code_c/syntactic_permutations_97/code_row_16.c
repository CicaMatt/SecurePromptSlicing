#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_LEN 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_LEN];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

int user_exists(const char *username) {
    FILE *fp = fopen(DB_FILE, "rb");
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

void hash_password(const char *password, unsigned char *output) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(const User *user) {
    FILE *fp = fopen(DB_FILE, "ab");
    if (!fp) return 0;
    
    fwrite(user, sizeof(User), 1, fp);
    fclose(fp);
    return 1;
}

int main() {
    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];
    User new_user;

    printf("Enter username: ");
    scanf("%99s", username);
    
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Enter password: ");
    scanf("%99s", password);

    printf("Enter first name: ");
    scanf("%99s", first_name);

    printf("Enter last name: ");
    scanf("%99s", last_name);

    printf("Enter email: ");
    scanf("%99s", email);

    strcpy(new_user.username, username);
    hash_password(password, new_user.password_hash);

    if (register_user(&new_user)) {
        printf("Registration succeeded.\n");
    } else {
        printf("Failed to register user.\n");
    }

    return 0;
}