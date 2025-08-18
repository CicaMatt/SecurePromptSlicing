#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define EMAIL_LENGTH 256

int unsubscribe(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open("subscribers.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[512];
    snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email='%q';", email);

    rc = sqlite3_exec(db, query, 0, 0, 0);
    if (rc == SQLITE_OK) {
        printf("You have been unsubscribed.\n");
    } else {
        printf("Email not found in the database.\n");
    }

    sqlite3_close(db);
    return rc == SQLITE_OK;
}

int main() {
    char email[EMAIL_LENGTH];
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}