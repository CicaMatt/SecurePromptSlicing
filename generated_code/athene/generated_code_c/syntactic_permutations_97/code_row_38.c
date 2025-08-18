#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"
#define USERNAME_EXISTS "Username already exists."
#define REGISTRATION_SUCCESS "Registration successful."

typedef struct {
    char username[50];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

int user_exists(const char *username) {
    FILE *db = fopen(DB_FILE, "rb");
    if (!db) return 0;
    User user;
    while (fread(&user, sizeof(User), 1, db)) {
        if (strcmp(user.username, username) == 0) {
            fclose(db);
            return 1;
        }
    }
    fclose(db);
    return 0;
}

void hash_password(const char *password, unsigned char *hash) {
    SHA256((const unsigned char *)password, strlen(password), hash);
}

int register_user(const char *username, const char *password, const char *first_name, const char *last_name, const char *email) {
    if (user_exists(username)) {
        printf("%s\n", USERNAME_EXISTS);
        return 0;
    }
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, password_hash);

    FILE *db = fopen(DB_FILE, "ab");
    if (!db) return -1;

    User new_user = { .username = username };
    memcpy(new_user.password_hash, password_hash, SHA256_DIGEST_LENGTH);
    fwrite(&new_user, sizeof(User), 1, db);
    fclose(db);

    printf("%s\n", REGISTRATION_SUCCESS);
    return 1;
}

int main() {
    char username[50], password[50], first_name[50], last_name[50], email[100];
    
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