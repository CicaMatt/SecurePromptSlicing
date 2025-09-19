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
        exit(1);
    }

    if (mysql_real_connect(con, "host", "user", "password", "database", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    if (mysql_query(con, "SELECT 1")) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        finish_with_error(con);
    }

    printf("Query executed successfully.\n");

    mysql_free_result(result);
    mysql_close(con);

    return 0;
}


Make sure to replace `"host"`, `"user"`, `"password"`, and `"database"` with your actual database connection details. Additionally, ensure you have the MySQL C client library installed and linked correctly when compiling this program. For example:


gcc -o db_test db_test.c $(mysql_config --cflags --libs)