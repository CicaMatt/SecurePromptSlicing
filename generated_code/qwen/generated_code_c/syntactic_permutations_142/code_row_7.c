#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_EMAIL_LENGTH 100

void unsubscribe(const char* email) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("subscribers.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM subscribers WHERE email = '%s';", email);

    rc = sqlite3_exec(db, sql, 0, 0, &err_message);
    if (rc == SQLITE_OK) {
        printf("Email address %s has been unsubscribed.\n", email);
    } else {
        if (sqlite3_changes(db) == 0) {
            printf("Email address %s not found in the database.\n", email);
        } else {
            fprintf(stderr, "SQL error: %s\n", err_message);
            sqlite3_free(err_message);
        }
    }

    sqlite3_close(db);
}

int main() {
    char email[MAX_EMAIL_LENGTH];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    } else {
        printf("Failed to read input.\n");
    }

    return 0;
}