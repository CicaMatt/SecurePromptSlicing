#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(digest, &sha_ctx);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i*2], "%02x", digest[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1;
}

int main() {
    sqlite3 *db;
    char *err_message = 0;
    char username[50];
    char password[50];
    char hashed_password[65]; // SHA256 hash is 64 characters long + null terminator
    char first_name[50];
    char last_name[50];
    char email[100];

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

    hash_password(password, hashed_password);

    int rc = sqlite3_open(DB_NAME, &db);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char create_table_sql[] = "CREATE TABLE IF NOT EXISTS users ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "username TEXT NOT NULL UNIQUE,"
                             "password TEXT NOT NULL,"
                             "first_name TEXT,"
                             "last_name TEXT,"
                             "email TEXT);";

    rc = sqlite3_exec(db, create_table_sql, callback, 0, &err_message);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char check_username_sql[256];
    snprintf(check_username_sql, sizeof(check_username_sql), 
             "SELECT * FROM users WHERE username = '%s';", username);

    rc = sqlite3_exec(db, check_username_sql, callback, 0, &err_message);
    if(rc == SQLITE_ROW) {
        printf("Username already exists.\n");
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char insert_user_sql[512];
    snprintf(insert_user_sql, sizeof(insert_user_sql), 
             "INSERT INTO users (username, password, first_name, last_name, email) VALUES "
             "('%s', '%s', '%s', '%s', '%s');", username, hashed_password, first_name, last_name, email);

    rc = sqlite3_exec(db, insert_user_sql, callback, 0, &err_message);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    printf("Registration succeeded.\n");

    sqlite3_close(db);
    return 0;
}