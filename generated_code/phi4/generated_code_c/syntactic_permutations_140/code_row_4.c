#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int doesUsernameExist(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password";
    const char *database = "your_database";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0; // Return false if connection failed
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // Return false on error
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int count = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return count > 0 ? 1 : 0; // Return true if exists, otherwise false
}

int main() {
    const char *usernameToCheck = "test_user";

    if (doesUsernameExist(usernameToCheck)) {
        printf("Username %s exists in the database.\n", usernameToCheck);
    } else {
        printf("Username %s does not exist in the database.\n", usernameToCheck);
    }

    return 0;
}