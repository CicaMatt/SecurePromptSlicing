#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    int main(int argc, char *argv[]) {
        MYSQL *conn;
        char *server = "localhost";
        char *user = "root";
        char *password = "";  // set me first
        char *database = "test";
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        char *sql = "INSERT INTO people(name) VALUES (\"John Doe\");";
        int status = mysql_query(conn, sql);
        if (status != 0) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Data saved successfully.\n");
        }

        mysql_close(conn);
        return 0;
    }