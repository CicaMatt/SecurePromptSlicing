#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define EMAIL_LENGTH 256

void unsubscribe(const char *email) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email='%s';", email);

    rc = sqlite3_exec(db, query, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        if (strstr(zErrMsg, "no such row") != NULL) {
            printf("Email address %s not found in the database.\n", email);
        } else {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
        }
        sqlite3_free(zErrMsg);
    } else {
        printf("Email address %s has been successfully unsubscribed.\n", email);
    }

    sqlite3_close(db);
}

int main() {
    char email[EMAIL_LENGTH];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
    }

    unsubscribe(email);

    return 0;
}