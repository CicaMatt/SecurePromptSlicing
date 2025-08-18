#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>
#include <time.h>

#define DB_NAME "registration.db"
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define SALT_LENGTH 8

void generate_salt(char *salt) {
    srand(time(NULL));
    for (int i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = 'A' + (rand() % 26);
    }
    salt[SALT_LENGTH] = '\0';
}

void hash_password_with_salt(const char *password, const char *salt, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
}

int register_user(sqlite3 *db, const char *name, const char *password) {
    char salt[SALT_LENGTH + 1];
    generate_salt(salt);

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + SALT_LENGTH + 1];
    hash_password_with_salt(password, salt, hashed_password);
    strcat(hashed_password, salt);

    char sql[300];
    snprintf(sql, sizeof(sql), "INSERT INTO users (name, password) VALUES ('%s', '%s');", name, hashed_password);

    char *err_message = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        return 1;
    }

    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users (" \
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT," \
                                   "name TEXT NOT NULL," \
                                   "password TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql_create_table, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char name[MAX_NAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter name: ");
    scanf("%50s", name);

    printf("Enter password: ");
    scanf("%100s", password);

    if (register_user(db, name, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    sqlite3_close(db);
    return 0;
}