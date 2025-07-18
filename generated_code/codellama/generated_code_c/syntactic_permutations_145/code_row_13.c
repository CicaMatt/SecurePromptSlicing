#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main()
{
    // Connect to database.
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password",
                            "database", 0, NULL, 0))
    {
        printf("Error connecting to database.\n");
        return -1;
    }

    // Insert stock into database.
    char *stock_name = get_stock_name();
    char insert_query[256];
    sprintf(insert_query, "INSERT INTO stocks (name) VALUES (\"%s\")", stock_name);
    if (mysql_query(conn, insert_query))
    {
        printf("Error inserting into database.\n");
        return -1;
    }

    // Call buy_function with stock name as argument.
    buy_function(stock_name);

    return 0;
}