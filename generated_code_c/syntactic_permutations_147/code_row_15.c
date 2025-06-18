#include <stdio.h>
    #include <stdlib.h> //required for exit function
    #include <string.h> // required for strcmp function
    #include <mysql/mysql.h>

    int main(int argc, char **argv){
        if (argc != 3) {
            printf("Usage: buy_order stockname quantity");
            exit(1);
        }

        // connect to the database
        MYSQL *conn;
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "root", "mypasswd", "stocks", 0, NULL, 0)) {
            printf("Error connecting to database: %s\n", mysql_error(conn));
            exit(1);
        }

        // insert into the table
        char query[256];
        sprintf(query, "INSERT INTO orders (stockname, quantity) VALUES ('%s', '%d')",
                argv[1], atoi(argv[2]));
        if (mysql_query(conn, query)) {
            printf("Error making database query: %s\n", mysql_error(conn));
            exit(1);
        }

        // redirect to the stock view page
        char url[64];
        sprintf(url, "http://localhost/stock_view?stockname=%s&quantity=%d", argv[1], atoi(argv[2]));
        printf("Location: %s\n\n", url);
        exit(0);
    }