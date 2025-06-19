#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void insert_user_message_in_db(char *username, char *message) {
    sqlite3 *db;
    int rc;
    char *error_msg = 0;
    char sql[150];

    rc = sqlite3_open("messages.sqlite", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message);
    rc = sqlite3_exec(db, sql, 0, 0, &error_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        sqlite3_close(db);
        return;
    }

    sqlite3_close(db);
}

void display_messages() {
    sqlite3 *db;
    int rc;
    char *error_msg = 0;
    char sql[150];

    sprintf(sql, "SELECT * FROM messages");
    rc = sqlite3_exec(db, sql, display_message_callback, 0, &error_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", error_msg);
        sqlite3_free(error_msg);
        return;
    }
}

void display_message_callback(void *data, int num_fields, char **fields, char **column_names) {
    for (int i = 0; i < num_fields; i++) {
        printf("%s: %s\n", column_names[i], fields[i]);
    }
}