#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int doesUsernameExist(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 0;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "your_database_name", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    row = mysql_fetch_row(res);
    int exists = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return exists > 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    int result = doesUsernameExist(username);

    if (result) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}


Make sure to replace `"your_database_name"` with the actual name of your database, and provide appropriate username and password for the MySQL connection in `mysql_real_connect()`.