#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define DB_FILE "users.db"

void handle_error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

const unsigned char* hash_password(const unsigned char *password, size_t password_len, unsigned char **hash, size_t *hash_len) {
    const EVP_MD *md_type = EVP_sha256();
    if (!EVP_Digest(password, password_len, NULL, hash_len, md_type)) {
        handle_error("Error hashing password");
    }
    
    *hash = malloc(*hash_len);
    if (!*hash || !EVP_Digest(password, password_len, *hash, hash_len, md_type)) {
        free(*hash);
        handle_error("Error allocating memory for hash");
    }

    return *hash;
}

int callback(void *data, int argc, char **argv, char **azColName) {
    if (argc > 0 && strcmp(argv[0], "username") == 0) {
        *(char**) data = argv[1];
    }
    return 0;
}

int check_username_exists(sqlite3 *db, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username='%s'", username);
    
    char *existing_user = NULL;
    int rc = sqlite3_exec(db, query, callback, &existing_user, NULL);

    if (rc != SQLITE_OK) {
        handle_error("Failed to execute query");
    }

    int exists = existing_user ? 1 : 0;
    free(existing_user);
    return exists;
}

int insert_user(sqlite3 *db, const char *username, const unsigned char *hashed_password, size_t password_len) {
    sqlite3_stmt *stmt;
    
    const char *sql = "INSERT INTO users(username, hashed_password) VALUES(?, ?)";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        handle_error("Failed to prepare statement");
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, password_len, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        handle_error("Failed to insert user");
    }

    sqlite3_finalize(stmt);
    return 0;
}

void initialize_database(sqlite3 *db) {
    char *err_msg = NULL;

    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS users (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT, " \
        "username TEXT UNIQUE NOT NULL, " \
        "hashed_password BLOB NOT NULL);";

    int rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        handle_error("Failed to create table");
    }
}

int main() {
    sqlite3 *db;
    char username[100], password[100], first_name[50], last_name[50], email[100];

    if (sqlite3_open(DB_FILE, &db)) {
        handle_error("Can't open database");
    }

    initialize_database(db);

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    printf("Enter first name: ");
    fgets(first_name, sizeof(first_name), stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Enter last name: ");
    fgets(last_name, sizeof(last_name), stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    if (check_username_exists(db, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned char *hashed_password;
        size_t hash_len;
        const unsigned char* result = hash_password((unsigned char*)password, strlen(password), &hashed_password, &hash_len);

        insert_user(db, username, result, hash_len);
        free(hashed_password);

        printf("Registration succeeded.\n");
    }

    sqlite3_close(db);
    return 0;
}