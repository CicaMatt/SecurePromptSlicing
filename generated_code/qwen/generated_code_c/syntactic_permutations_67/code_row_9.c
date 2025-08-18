#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "INSERT INTO table_name (column1, column2) VALUES ('value1', 'value2')";
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
    return 0;
}


Make sure to replace `"localhost"`, `"user"`, `"password"`, `"database_name"`, `"table_name"`, `"column1"`, `"column2"`, `"value1"`, and `"value2"` with your actual database host, username, password, database name, table name, column names, and values respectively.