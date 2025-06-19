#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// include mysql header file
#include "mysql/mysql.h"

int main()
{
    MYSQL *conn;
    // create connection object
    conn = mysql_init(NULL);

    // connect to server with default database and user
    if (!mysql_real_connect(conn, "localhost", "user", "password", "dbname", 0, NULL, 0)) {
        fprintf(stderr, "Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
    }

    // create a SQL statement and execute it
    char *sql = "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('username', 'password', 'firstname', 'lastname', 'email@example.com')";
    mysql_query(conn, sql);

    // get the result of the query
    MYSQL_RES *result = mysql_store_result(conn);

    int num_rows;

    // fetch all rows from result set
    while ((row = mysql_fetch_row(result))) {
        num_rows++;
    }

    printf("%d row inserted", num_rows);

    // close connection object
    mysql_close(conn);

    return 0;
}