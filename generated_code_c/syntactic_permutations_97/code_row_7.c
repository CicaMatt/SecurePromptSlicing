#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "root";
    char *password = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *database = "mydb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        printf("Error connecting to the database\n");
    }

    char *username = "johndoe";
    char *password = "mysecretpassword";
    int length = strlen(username) + strlen(password) + 2;
    char query[length];
    sprintf(query, "SELECT username FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query))
    {
        printf("Error: %s\n", mysql_error(conn));
    }

    res = mysql_store_result(conn);

    int numRows = mysql_num_rows(res);
    if (numRows == 1)
    {
        printf("User already exists\n");
    }

    else
    {
        sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, password);

        if (mysql_query(conn, query))
        {
            printf("Error: %s\n", mysql_error(conn));
        }

        printf("Registration successful\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}