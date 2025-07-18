#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    int main() {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        char *server = "localhost";
        char *user = "root";
        char *password = "12345678";
        char *database = "mydb";

        conn = mysql_init(NULL);

        /* Connect to database */
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        /* Insert data into the table */
        char query[256] = {0};
        printf("Enter username: ");
        scanf("%s", query);
        strcat(query, ", '");
        printf("Enter password: ");
        scanf("%s", query);
        strcat(query, "'");

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        /* Close connection */
        mysql_close(conn);
    }