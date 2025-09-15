#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int doesUsernameExist(const char *host, const char *user, const char *password,
                      const char *database, const char *username) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 0;
    }

    if (!mysql_real_connect(&conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection to database failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 0;
    }

    res = mysql_use_result(&conn);

    if ((row = mysql_fetch_row(res))) {
        int count = atoi(row[0]);
        mysql_free_result(res);
        mysql_close(&conn);
        return (count > 0) ? 1 : 0;
    } else {
        fprintf(stderr, "Error fetching result: %s\n", mysql_error(&conn));
    }

    mysql_free_result(res);
    mysql_close(&conn);
    return 0;
}

int main() {
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "testdb";

    const char *usernameToCheck = "exampleUser";

    if (doesUsernameExist(host, user, password, database, usernameToCheck)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
