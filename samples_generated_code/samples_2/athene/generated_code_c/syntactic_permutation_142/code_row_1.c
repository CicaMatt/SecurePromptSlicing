#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(char *email) {
    sqlite3 *db;
    int rc;
    char sql[100];
    const char *data = "Callback function called";

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE email='%s'", email);
    
    int count = 0;
    rc = sqlite3_get_table(db, sql, &result, &row, &column, &errormsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errormsg);
        sqlite3_free(errormsg);
        return;
    }
    sscanf(result[1], "%d", &count);
    sqlite3_free_table(result);

    if (count > 0) {
        snprintf(sql, sizeof(sql), "DELETE FROM users WHERE email='%s'", email);
        rc = sqlite3_exec(db, sql, NULL, 0, &errormsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errormsg);
            sqlite3_free(errormsg);
        } else {
            printf("You have been unsubscribed.\n");
        }
    } else {
        printf("Email address not found. You are already unsubscribed.\n");
    }

    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email);
    unsubscribe(email);
    return 0;
}