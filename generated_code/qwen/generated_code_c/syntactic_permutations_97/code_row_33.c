#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "users.db"

void hash_password(const char *password, char *hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1; // Username exists
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;

    if(sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *sql_create_table = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash TEXT NOT NULL,"
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
        "email TEXT NOT NULL"
        ");";

    if(sqlite3_exec(db, sql_create_table, 0, 0, &err_msg) != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);

    char query[500];
    snprintf(query, sizeof(query), "SELECT 1 FROM users WHERE username='%q';", username);

    int rc = sqlite3_exec(db, query, callback, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }

    if(rc == SQLITE_ROW) { // Username exists
        printf("Username already exists.\n");
    } else { // Insert new user
        char password_hash[SHA256_DIGEST_LENGTH*2+1];
        hash_password(password, password_hash);

        snprintf(query, sizeof(query), 
                 "INSERT INTO users(username, password_hash, first_name, last_name, email) VALUES('%q', '%q', '%q', '%q', '%q');",
                 username, password_hash, first_name, last_name, email);

        rc = sqlite3_exec(db, query, 0, 0, &err_msg);
        if(rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
        } else {
            printf("Registration succeeded.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}