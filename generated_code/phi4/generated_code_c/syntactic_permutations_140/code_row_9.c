#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main() {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    if (mysql_query(con, "SELECT VERSION();")) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con);
    }

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        printf("Database version: %s\n", row[0]);
    }

    mysql_free_result(result);
    mysql_close(con);

    return 0;
}


**Note**: Replace `"localhost"`, `"username"`, `"password"`, and `"database_name"` with your actual database server details. Make sure the MySQL client library is installed on your system for this code to compile and run successfully. You might need to link against the `mysqlclient` library by compiling with `-lmysqlclient`.