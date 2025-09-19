#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int doesUsernameExist(const char *host, const char *user, const char *password, const char *database, const char *usernameToCheck) {
    MYSQL conn;
    MYSQL_RES *result;
    MYSQL_ROW row;

    // Initialize connection
    mysql_init(&conn);

    // Connect to database
    if (!mysql_real_connect(&conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(&conn));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", mysql_real_escape_string(&conn, (char *)usernameToCheck));

    // Execute the query
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    result = mysql_store_result(&conn);

    if (result) {
        row = mysql_fetch_row(result);
        int count = atoi(row[0]);
        mysql_free_result(result);

        // Close connection
        mysql_close(&conn);

        return count > 0;
    } else {
        fprintf(stderr, "Result error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }
}

int main() {
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "test_db";

    const char *usernameToCheck = "example_user";

    int exists = doesUsernameExist(host, user, password, database, usernameToCheck);

    if (exists) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
