#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = "your_database_name"; // replace with your database name
    const char *server = "localhost";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *query = "SELECT EXISTS(SELECT 1 FROM users WHERE username='your_username') AS exists;"; // replace 'your_username' with actual username
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        int exists = atoi(row[0]);
        printf("%d\n", exists);
    } else {
        fprintf(stderr, "Error fetching result: %s\n", mysql_error(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
