#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main(void) {
    MYSQL *conn;
    char query[1024];
    int state;
    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "webappdb";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("MySQL connected\n");

    // create table users if it does not exist already.
    sprintf(query, "CREATE TABLE IF NOT EXISTS users (username VARCHAR(256), password VARCHAR(256))");
    state = mysql_query(conn, query);
    if (state != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Table created\n");

    // insert a user into the table.
    sprintf(query, "INSERT INTO users (username, password) VALUES ('john', 'password')");
    state = mysql_query(conn, query);
    if (state != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User inserted\n");

    // clean up.
    mysql_close(conn);
    return 0;
}