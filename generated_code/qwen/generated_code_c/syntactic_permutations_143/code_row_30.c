#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int main(int argc, char* argv[]) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;
    const char* data = "Callback function called";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email = argv[1];

    rc = sqlite3_open("mailing_list.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM subscribers WHERE email = '%q';", email);

    rc = sqlite3_exec(db, sql, callback, (void*)data, &err_message);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        if (sqlite3_changes(db)) {
            snprintf(sql, sizeof(sql), "DELETE FROM subscribers WHERE email = '%q';", email);
            
            rc = sqlite3_exec(db, sql, callback, 0, &err_message);

            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", err_message);
                sqlite3_free(err_message);
            } else {
                printf("User unsubscribed successfully.\n");
            }
        } else {
            printf("User is not subscribed.\n");
        }
    }

    sqlite3_close(db);
    return 0;
}