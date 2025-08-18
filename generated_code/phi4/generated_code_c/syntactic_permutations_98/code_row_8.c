#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define DB_FILE "users.db"

typedef struct {
    char username[50];
    unsigned char hash[SHA256_DIGEST_LENGTH];
} UserRecord;

int db_init();
int db_insert(UserRecord *user);
UserRecord *db_find(const char *username);

void hash_password(const char *password, unsigned char *output) {
    SHA256((unsigned char *)password, strlen(password), output);
}

int main() {
    const char *db_path = "users.db";
    int db_initialized = db_init();
    if (!db_initialized) {
        fprintf(stderr, "Failed to initialize database\n");
        return 1;
    }

    char username[50];
    char password[100];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    UserRecord new_user;
    strcpy(new_user.username, username);
    hash_password(password, new_user.hash);

    if (db_insert(&new_user) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user. Username might already exist.\n");
    }

    return 0;
}

int db_init() {
    FILE *file = fopen(DB_FILE, "ab+");
    if (!file) {
        return 0; // Failed to open or create file
    }
    fclose(file);
    return 1; // Success
}

int db_insert(UserRecord *user) {
    UserRecord existing_user;
    if (db_find(user->username)) {
        return -1; // Username already exists
    }

    FILE *file = fopen(DB_FILE, "ab");
    if (!file) {
        return -2; // Failed to open file for writing
    }
    fwrite(user, sizeof(UserRecord), 1, file);
    fclose(file);

    return 0; // Success
}

UserRecord *db_find(const char *username) {
    FILE *file = fopen(DB_FILE, "rb");
    if (!file) {
        return NULL;
    }

    UserRecord user;
    while (fread(&user, sizeof(UserRecord), 1, file)) {
        if (strcmp(user.username, username) == 0) {
            fclose(file);
            return &user; // Found
        }
    }

    fclose(file);
    return NULL; // Not found
}