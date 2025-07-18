#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void insert_user_message_in_db(char* username, char* message) {
    sqlite3 *db;
    int rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) {
        printf("Error opening database: %s\n", sqlite3_errmsg(db));
    }
    char* errorMessage = 0;
    char sql[100];
    sprintf(sql, "INSERT INTO messages VALUES ('%s', '%s')", username, message);
    rc = sqlite3_exec(db, sql, NULL, 0, &errorMessage);
    if (rc != SQLITE_OK ) {
        printf("SQL error: %s\n", errorMessage);
    }
    sqlite3_close(db);
}

void post() {
    char* username = get_username();
    char* message = get_message();
    insert_user_message_in_db(username, message);
    redirect_to("index.html");
}