#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sqlite3.h>
    #include <openssl/sha.h>
    #include <crypt.h>
    #define SHA256_DIGEST_LENGTH 32

    int main(void) {
        // Create a database to store user accounts.
        sqlite3 *db;
        char *err_msg = 0;
        int rc = sqlite3_open("database.db", &db);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
        // Create a table in the database to store user accounts.
        char *sql = "CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)";
        rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
        if (rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 1;
        }
        // Register a new user.
        char username[20];
        char password[20];
        printf("Enter Username: ");
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);
        // Hash the password before storing it in the database.
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char *)password, strlen(password), hash);
        // Convert the hash to a hexadecimal string.
        size_t len = sizeof(hash) * 2 + 1;
        char password_hex[len];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            sprintf(&password_hex[i*2], "%02x", hash[i]);
        }
        // Insert the username and password into the database.
        char *insert = "INSERT INTO users (username, password) VALUES ('%s', '%s')";
        rc = sqlite3_exec(db, insert, NULL, 0, &err_msg);
        if (rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 1;
        }
        // Close the database.
        rc = sqlite3_close(db);
        if (rc != SQLITE_OK ) {
            fprintf(stderr, "Failed to close database.\n");
            return 1;
        }
        return 0;
    }