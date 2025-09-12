#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function to return a database connection
sqlite3* get_db_connection() {
    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

// Function to return the server name
const char* get_server_name() {
    return "localhost";
}

// Function to return the database name
const char* get_database_name() {
    return "example.db";
}

// Function to return the database user
const char* get_database_user() {
    return "user";
}

int main() {
    sqlite3 *db = get_db_connection();
    if (db != NULL) {
        printf("Database connection established.\n");
        printf("Server Name: %s\n", get_server_name());
        printf("Database Name: %s\n", get_database_name());
        printf("Database User: %s\n", get_database_user());
        sqlite3_close(db);
    } else {
        printf("Failed to connect to the database.\n");
    }
    return 0;
}