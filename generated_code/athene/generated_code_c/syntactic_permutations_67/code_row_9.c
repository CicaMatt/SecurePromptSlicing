#include <stdio.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char server[] = "localhost";
    char user[] = "root";
    char password[] = "your_password"; // replace with your password
    char database[] = "test_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS example (id INT AUTO_INCREMENT PRIMARY KEY, value VARCHAR(255))";
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    sql = "INSERT INTO example (value) VALUES ('Hello World')";
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    sql = "SELECT * FROM example";
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    res = mysql_store_result(conn);
    if (res) {
        while ((row = mysql_fetch_row(res))) {
            printf("ID %s Value %s\n", row[0], row[1]);
        }
        mysql_free_result(res);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);

    return 0;
}