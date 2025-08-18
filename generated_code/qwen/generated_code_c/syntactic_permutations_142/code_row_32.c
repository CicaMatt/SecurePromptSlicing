#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "emails.db"

int unsubscribe(const char* email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM subscribers WHERE email = '%s';", email);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc == SQLITE_OK) {
        printf("Email address removed successfully.\n");
    } else {
        if (sqlite3_changes(db) == 0) {
            printf("Email address not found in the database.\n");
        } else {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
        }
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    } else {
        printf("Failed to read email address.\n");
    }

    return 0;
}