#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_SIZE 100
#define DB_FILE "users.db"

typedef struct {
    char username[MAX_SIZE];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

int user_exists(const char *username) {
    FILE *file = fopen(DB_FILE, "rb");
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

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

void register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("Username already exists.\n");
        return;
    }

    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    FILE *file = fopen(DB_FILE, "ab");
    if (!file) {
        printf("Error opening database file.\n");
        return;
    }

    User user = {0};
    strncpy(user.username, username, MAX_SIZE - 1);
    memcpy(user.password_hash, password_hash, SHA256_DIGEST_LENGTH);

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    printf("Registration succeeded.\n");
}

int main() {
    char username[MAX_SIZE], password[MAX_SIZE], first_name[MAX_SIZE], last_name[MAX_SIZE], email[MAX_SIZE];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    register_user(username, password, first_name, last_name, email);

    return 0;
}