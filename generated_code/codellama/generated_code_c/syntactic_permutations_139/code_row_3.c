#include <stdio.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>

    int main(void){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        char *server = getenv("DB_SERVER");
        char *user = getenv("DB_USERNAME");
        char *password = getenv("DB_PASSWORD");
        char *dbname = getenv("DB_NAME");

        conn = mysql_init(NULL);

        /* Connect to database */
        if (!mysql_real_connect(conn, server, user, password, dbname, 0, NULL, 0)) {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            return 1;
        }

        /* send SQL query */
        if (mysql_query(conn, "SELECT * FROM Users WHERE user = 'username' AND role = 'moderator'")) {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            return 1;
        }

        res = mysql_store_result(conn);

        /* output table */
        while ((row = mysql_fetch_row(res)) != NULL) {
            if (strcmp("moderator", row[2]) == 0)
                return true;
        }

        return false;
    }