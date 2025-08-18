#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Your database password
    const char *database = "your_database_name";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    row = mysql_fetch_row(res);
    int count = atoi(row[0]);
    mysql_free_result(res);
    mysql_close(conn);

    return count > 0 ? 1 : 0;
}

int main() {
    const char *username = "test_user";
    if (check_username_exists(username)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }
    return 0;
}