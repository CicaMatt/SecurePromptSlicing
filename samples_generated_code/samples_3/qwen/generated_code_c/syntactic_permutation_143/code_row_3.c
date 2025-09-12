#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int check_and_unsubscribe_user(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char *err_msg = 0;
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM users WHERE email='%s';", email);
    
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc == SQLITE_OK) {
        printf("User unsubscribed successfully.\n");
    } else {
        if (strcmp(err_msg, "SQL logic error or missing database") == 0) {
            printf("User is not subscribed.\n");
        } else {
            fprintf(stderr, "SQL error: %s\n", err_msg);
        }
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);
    return rc;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    check_and_unsubscribe_user(email);

    return 0;
}