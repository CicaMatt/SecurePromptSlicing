#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

/*
 * Returns true if email in database, otherwise returns false
 */
int is_email_in_database(const char *email) {
    // Open database connection
    sqlite3 *db;
    int rc = sqlite3_open("user_data", &db);

    if (rc != SQLITE_OK) {
        printf("Database error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    char sql[] = "SELECT email FROM user WHERE email=?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Bind email to the statement
    rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        printf("Binding error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Step through the statement
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        // Email found in database
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    } else if (rc == SQLITE_DONE) {
        // No email found in database
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    } else {
        printf("Step error: %s\n", sqlite3_errmsg(db));
        return 0;
    }
}

/*
 * Deletes user from the database and unsubscribes from the mailing list.
 */
void delete_user_from_database_and_unsubscribe(const char *email) {
    // Open database connection
    sqlite3 *db;
    int rc = sqlite3_open("user_data", &db);

    if (rc != SQLITE_OK) {
        printf("Database error: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Prepare the SQL statement for delete
    sqlite3_stmt *stmt;
    char sql[] = "DELETE FROM user WHERE email=?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind email to the delete statement
    rc = sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        printf("Binding error: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Step through the delete statement
    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        printf("Delete step error: %s\n", sqlite3_errmsg(db));
        return;
    } else {
        printf("User successfully deleted from database.\n");
    }

    // Finalize the delete statement
    rc = sqlite3_finalize(stmt);

    if (rc != SQLITE_OK) {
        printf("Delete finalize error: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Unsubscribe from the mailing list
    unsubscribe_user_from_mailing_list(email);
}

/*
 * Handles the GET request to the unsubscribe endpoint.
 */
void handle_get_unsubscribe_request(const char *email) {
    if (is_email_in_database(email)) {
        delete_user_from_database_and_unsubscribe(email);
    } else {
        printf("Email not in database, no need to unsubscribe.\n");
    }
}

int main(void) {
    handle_get_unsubscribe_request("johnsmith@example.com");
    return 0;
}