#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_username_exists(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Replace with your MySQL password
    const char *database = "your_database_name"; // Replace with your database name

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0; // Username does not exist
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int user_count = atoi(row[0]);

    mysql_free_result(res);
    mysql_close(conn);

    return user_count > 0;
}

int main() {
    const char *username_to_check = "test_user"; // Replace with the username you want to check

    if (check_username_exists(username_to_check)) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    return 0;
}
 

Make sure to replace `"your_database_name"`, `"root"` and `""` with your actual database name, MySQL username, and password respectively. Also, ensure that you have the MySQL client library installed in your environment. You may need to link against the MySQL client library when compiling this code using `-lmysqlclient`.