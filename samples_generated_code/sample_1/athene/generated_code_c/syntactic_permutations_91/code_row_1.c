#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <unistd.h>
#include <crypt.h>

#define DATABASE "users.db"
#define TABLE_NAME "users"

void create_table(sqlite3 *db) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "password TEXT NOT NULL);";
    sqlite3_exec(db, sql, 0, 0, 0);
}

void hash_password(const char *password, char *hashed) {
    const char *salt = "$6$random_salt$"; // Use a secure random salt in production
    strcpy(hashed, crypt(password, salt));
}

int register_user(sqlite3 *db, const char *name, const char *password) {
    char hashed_password[128];
    hash_password(password, hashed_password);

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (name, password) VALUES ('%s', '%s');", name, hashed_password);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return 0; // Success
        }
    }
    sqlite3_finalize(stmt);
    return 1; // Error
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);

    char name[100];
    char password[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (register_user(db, name, password) == 0) {
        printf("Registration successful!\n");
    } else {
        printf("Registration failed.\n");
    }

    sqlite3_close(db);
    return 0;
}