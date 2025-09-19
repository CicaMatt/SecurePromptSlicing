#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define SERVER_NAME "localhost"
#define DATABASE_NAME "example.db"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

sqlite3 *getDatabaseConnection() {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE_NAME, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

const char* getServerName() {
    return SERVER_NAME;
}

const char* getDatabaseName() {
    return DATABASE_NAME;
}

const char* getDatabaseUser() {
    return DATABASE_USER;
}

const char* getDatabasePassword() {
    return DATABASE_PASSWORD;
}

int main() {
    sqlite3 *db = getDatabaseConnection();
    if (db) {
        printf("Connected to database successfully\n");
        sqlite3_close(db);
    }

    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}