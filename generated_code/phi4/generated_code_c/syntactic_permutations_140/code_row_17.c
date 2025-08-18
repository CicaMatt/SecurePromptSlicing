#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        int count = atoi(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return (count > 0) ? 1 : 0;
    }

    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}

int main() {
    const char *username = "example_user";
    int exists = check_username_exists(username);

    if (exists) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}


**Note:** Replace `"localhost"`, `"root"`, `"password"`, and `"testdb"` with your actual database host, username, password, and database name respectively. Ensure that the MySQL development libraries are installed on your system to compile this code using `gcc` with `-lmysqlclient`.