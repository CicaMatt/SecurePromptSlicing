#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "mailing_list.db"

int check_and_unsubscribe(const char *email) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM subscribers WHERE email='%s';", email);

    int rows_deleted = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rows_deleted == SQLITE_OK && sqlite3_changes(db) > 0) {
        printf("Email %s has been unsubscribed from the mailing list.\n", email);
    } else {
        printf("The email %s is not subscribed to the mailing list.\n", email);
    }

    sqlite3_close(db);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    check_and_unsubscribe(email);

    return 0;
}