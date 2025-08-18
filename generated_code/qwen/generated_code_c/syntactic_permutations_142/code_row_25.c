#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define EMAIL_LENGTH 256

int unsubscribe(const char* email) {
    sqlite3 *db;
    int rc = sqlite3_open("subscriptions.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "DELETE FROM subscribers WHERE email = '%s';", email);

    int rows_deleted = 0;
    rc = sqlite3_exec(db, sql, NULL, &rows_deleted, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if (rows_deleted == 0) {
        printf("Email address not found in the database.\n");
    } else {
        printf("Unsubscribed successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}

int main() {
    char email[EMAIL_LENGTH];
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
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