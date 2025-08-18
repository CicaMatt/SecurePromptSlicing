#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_EMAIL_LENGTH 100

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void remove_email_from_database(sqlite3 *db, const char *email) {
    char sql[256];
    sprintf(sql, "DELETE FROM subscribers WHERE email = '%s';", email);
    
    char *err_message = 0;
    int rc = sqlite3_exec(db, sql, callback, 0, &err_message);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Email address removed successfully.\n");
    }
}

void check_and_remove_email(sqlite3 *db, const char *email) {
    char sql[256];
    sprintf(sql, "SELECT * FROM subscribers WHERE email = '%s';", email);

    int rc = sqlite3_exec(db, sql, callback, 0, 0);
    
    if (rc == SQLITE_OK) {
        remove_email_from_database(db, email);
    } else {
        printf("Email address not found in the database.\n");
    }
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("subscribers.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    char email[MAX_EMAIL_LENGTH];
    printf("Enter your email address to unsubscribe: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    // Remove newline character if present
    size_t len = strlen(email);
    if (len > 0 && email[len - 1] == '\n') {
        email[len - 1] = '\0';
    }

    check_and_remove_email(db, email);

    sqlite3_close(db);
    return 0;
}