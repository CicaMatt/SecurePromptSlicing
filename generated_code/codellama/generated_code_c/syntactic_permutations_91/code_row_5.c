// Dependencies
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "sqlite3.h"
    #include <bcrypt.h>

    // Database connection
    sqlite3 *db;
    char *errMsg = 0;
    int rc = sqlite3_open("./database.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // User registration function
    int registerUser(char *username, char *password) {
        // Hash password
        char salt[10];
        bcrypt_gensalt(12, salt);
        char hashedPassword[64];
        bcrypt_hashpw(password, salt, hashedPassword);

        // Prepare SQL statement
        sqlite3_stmt *sql;
        const char *tail = 0;
        rc = sqlite3_prepare_v2(db, "INSERT INTO users (username, password) VALUES (?, ?)", -1, &sql, &tail);
        if (rc) {
            fprintf(stderr, "Can't prepare SQL statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
        sqlite3_bind_text(sql, 1, username, -1, 0);
        sqlite3_bind_text(sql, 2, hashedPassword, -1, 0);

        // Execute SQL statement
        rc = sqlite3_step(sql);
        if (rc) {
            fprintf(stderr, "Can't execute SQL statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
        sqlite3_finalize(sql);

        // Close database connection
        rc = sqlite3_close(db);
        if (rc) {
            fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
            return 1;
        }

        return 0;
    }

    // Main function
    int main() {
        char *username = "johndoe";
        char *password = "secret1234";
        registerUser(username, password);
        return 0;
    }